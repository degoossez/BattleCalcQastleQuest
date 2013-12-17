#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //attacker
    //class
    ui->AttClass->addItem("","");
    ui->AttClass->addItem("Forest","Forest");
    ui->AttClass->addItem("Death","Death");
    ui->AttClass->addItem("Air","Air");
    ui->AttClass->addItem("Earth","Earth");
    //curses
    ui->AttCurse->addItem("","");
    ui->AttCurse->addItem("Metamorphosis","Metamorphosis");
    ui->AttCurse->addItem("Suffocation","Suffocation");
    //item enchants
    ui->AttEnchant->addItem("","");
    ui->AttEnchant->addItem("Major Berserk","Major Berserk");
    ui->AttEnchant->addItem("Major Immunity","Major Immunity");
    //items
    ui->AttItem->addItem("","");
    ui->AttItem->addItem("Tormenter Touch","Tormenter Touch");
    ui->AttItem->addItem("Abyss Leech","Abyss Leech");
    ui->AttItem->addItem("Styx Cry","Styx Cry");
    ui->AttItem->addItem("Ancient Heart","Ancient Heart");
    ui->AttItem->addItem("Diamond Charm","Diamond Charm");
    ui->AttItem->addItem("Silver Jewel","Silver Jewel");
    //draugrs
    ui->AttItem->addItem("Leprous Seax","Leprous Seax");
    ui->AttItem->addItem("Corrupted Seax","Corrupted Seax");
    ui->AttItem->addItem("Massive Seax","Massive Seax");
    ui->AttItem->addItem("Contorted Seax","Contorted Seax");
    ui->AttItem->addItem("Spectral Seax","Spectral Seax");
    ui->AttItem->addItem("Acidic Seax","Acidic Seax");



    //defender
    //class
    ui->DefClass->addItem("","");
    ui->DefClass->addItem("Forest","Forest");
    ui->DefClass->addItem("Death","Death");
    ui->DefClass->addItem("Air","Air");
    ui->DefClass->addItem("Earth","Earth");
    //curses
    ui->DefCurse->addItem("","");
    ui->DefCurse->addItem("Metamorphosis","Metamorphosis");
    ui->DefCurse->addItem("Suffocation","Suffocation");
    //item enchants
    ui->DefEnchant->addItem("","");
    ui->DefEnchant->addItem("Major Berserk","Major Berserk");
    ui->DefEnchant->addItem("Major Immunity","Major Immunity");
    //items
    ui->DefItem->addItem("","");
    ui->DefItem->addItem("Tormenter Touch","Tormenter Touch");
    ui->DefItem->addItem("Abyss Leech","Abyss Leech");
    ui->DefItem->addItem("Styx Cry","Styx Cry");
    ui->DefItem->addItem("Ancient Heart","Ancient Heart");
    ui->DefItem->addItem("Diamond Charm","Diamond Charm");
    ui->DefItem->addItem("Silver Jewel","Silver Jewel");
    //draugrs
    ui->DefItem->addItem("Leprous Seax","Leprous Seax");
    ui->DefItem->addItem("Corrupted Seax","Corrupted Seax");
    ui->DefItem->addItem("Massive Seax","Massive Seax");
    ui->DefItem->addItem("Contorted Seax","Contorted Seax");
    ui->DefItem->addItem("Spectral Seax","Spectral Seax");
    ui->DefItem->addItem("Acidic Seax","Acidic Seax");
}
int teller,dip,attacker,defender;
int AttDmg,AttHealth,AttDef;
int DefDmg,DefHealth,DefDef;
int TempAttDmg,TempDefDmg,TempAttDef,TempDefDef,PreItemAttDmg,PreItemDefDmg;
int AttDefChange,DefDefChange;
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    dip=defender=attacker=0;
    for(int i=0;i<1000;i++)
    {
        ui->Result->clear();
        PreBattleCalc();
        attMIcalc(ui->AttEnchant->itemData(ui->AttEnchant->currentIndex()));
        defMIcalc(ui->DefEnchant->itemData(ui->DefEnchant->currentIndex()));
        while(AttHealth>0 && DefHealth>0 && teller<41)
        {
            calcDef();
            calcDmg();
            calcHealth();
            battle();
            teller++;
        }
        if(teller==40)
        {
            if(AttHealth<DefHealth)
            {
                ui->Result->append("Defender wins!");
            }
            else
            {
                ui->Result->append("Attacker wins!");
            }
        }
        else
        {
            if(AttHealth<=0 && DefHealth<=0)
            {
                ui->Result->append("Both creatures died!");
                dip++;
            }
            else if(AttHealth<=0)
            {
                ui->Result->append("Defender wins!");
                defender++;
            }
            else if(DefHealth<=0)
            {
                ui->Result->append("Attacker wins!");
                attacker++;
            }
        }
    }
    dip=dip/10;
    defender=defender/10;
    attacker=attacker/10;
    ui->Result->append("Dip:" + QString::number(dip) + "%");
    ui->Result->append("Attacker:" + QString::number(attacker) + "%");
    ui->Result->append("Defender:" + QString::number(defender) + "%");

}
void MainWindow::PreBattleCalc()
{
    AttDefChange=DefDefChange=0;
    teller=1;
    AttDmg=AttHealth=AttDef=0;
    DefDmg=DefHealth=DefDef=0;
    TempAttDmg=TempDefDmg=TempAttDef=TempDefDef=PreItemAttDmg=PreItemDefDmg=0;
    /*
    dus pre-battle berekent ge, ne keer voor de attacker en voor de defender:
    later programmeren (is gelijk aan battledmg:    draugrbattledmg = (basedmg*meta*draugritemmb)+addeddmg, met draugritemmb ofwel 1 ofwel 2.2
    draugrbattledef = draugrbasedef+addeddef --> da is de def voor als het draugr item van de opponent triggert, da moet ge de hele tijd berekenen zoals gewone def, en als het item die turn triggert, past ge deze def toe, en anders de gewone def. (tzelfde voor dmg)
    draugrbasedef is dus de def da uw crit heeft tegen de class van de opponent draugr item als die triggert (en de gewone basedef is de def tegen de class van de opponent crit)
    */

    double AttCurse = MainWindow::curse(ui->AttCurse->itemData(ui->AttCurse->currentIndex()));
    double AttMB = MainWindow::mbcalc(ui->AttEnchant->itemData(ui->AttEnchant->currentIndex()));
    /*
     *Attacker
     *battledmg = (basedmg*meta*mb)+addeddmg, met meta ofwel 1 ofwel "random getal tussen 0.01 en 0.6", en mb ofwel 1 ofwel 2.2
     */
    AttDmg = (ui->AttDmg->toPlainText().toInt() * AttCurse * AttMB)+ui->AttDmgIth->toPlainText().toInt();
    //battlehp = (basehp*meta)+addedhp
    AttHealth=(ui->AttHealth->toPlainText().toInt() * AttCurse) + ui->AttHealthIth->toPlainText().toInt();
    //battledef = basedef+addeddef (Mi zelf invullen)
    AttDef = getDefAttacker(ui->DefClass->itemData(ui->DefClass->currentIndex())) + ui->AttDefIth->value();

    double DefCurse = MainWindow::curse(ui->DefCurse->itemData(ui->DefCurse->currentIndex()));
    double DefMB = MainWindow::mbcalc(ui->DefEnchant->itemData(ui->DefEnchant->currentIndex()));
    /*
     *Defender
     *battledmg = (basedmg*meta*mb)+addeddmg, met meta ofwel 1 ofwel "random getal tussen 0.01 en 0.6", en mb ofwel 1 ofwel 2.2
     */
    DefDmg = (ui->DefDmg->toPlainText().toInt() * DefCurse * DefMB)+ui->DefDmgIth->toPlainText().toInt();
    //battlehp = (basehp*meta)+addedhp
    DefHealth= (ui->DefHealth->toPlainText().toInt() * DefCurse) + ui->DefHealthIth->toPlainText().toInt();
    //battledef = basedef+addeddef
    DefDef = getDefDefender(ui->AttClass->itemData(ui->AttClass->currentIndex())) + ui->DeffDefIth->value();
}
double MainWindow::curse(QVariant Curse)
{
    if(Curse.toString()=="Metamorphosis")
    {
        double random = qrand() % ((60+1) - 10)+10;
        random=random/100;
        return random;
    }
    else
    {
        return 1;
    }
}
double MainWindow::mbcalc(QVariant MB)
{
    if(MB.toString()=="Major Berserk")
    {
        return 2.1;
    }
    else
    {
        return 1;
    }
}
void MainWindow::attMIcalc(QVariant Item)
{
    if(Item.toString()=="Major Immunity")
    {
        AttDef=100;
    }
}
void MainWindow::defMIcalc(QVariant Item)
{
    if(Item.toString()=="Major Immunity")
    {
        DefDef=100;
    }
}
int MainWindow::getDefAttacker(QVariant Class)
{
    if(Class.toString()=="Forest")
    {
        return ui->AttFD->value();
    }
    if(Class.toString()=="Death")
    {
        return ui->AttDD->value();
    }
    if(Class.toString()=="Air")
    {
        return ui->AttAD->value();
    }
    if(Class.toString()=="Earth")
    {
        return ui->AttED->value();
    }
    return 0;
}
int MainWindow::getDefDefender(QVariant Class)
{
    if(Class.toString()=="Forest")
    {
        return ui->DefFD->value();
    }
    if(Class.toString()=="Death")
    {
        return ui->DefDD->value();
    }
    if(Class.toString()=="Air")
    {
        return ui->DefAD->value();
    }
    if(Class.toString()=="Earth")
    {
        return ui->DefED->value();
    }
    return 0;
}
void MainWindow::calcDef()
{
    TempAttDef=AttDef;
    TempDefDef=DefDef;
    itemDefEffectAttacker(ui->AttItem->itemData(ui->AttItem->currentIndex()));
    itemDefEffectDefender(ui->DefItem->itemData(ui->DefItem->currentIndex()));
}
void MainWindow::calcDmg()
{
    //nieuwedmg=(DmgVorigeRonde/((150-DefenseOpponentVorigeRonde)*100))*(150-DefenseOpponent)/100
    if(teller==1)
    {
    PreItemAttDmg=AttDmg*(150-DefDef)/100;
    PreItemDefDmg=DefDmg*(150-AttDef)/100;
    }
    else
    {
        if(TempDefDef-DefDef!=0) //als er verschil zit in de defense tussen de nieuwe en de vorige ronde moet de dmg opnieuw worden berekend
        {
            PreItemAttDmg=AttDmg*(150-DefDef)/100;
        }
        if(TempAttDef-AttDef!=0) //als er verschil zit in de defense tussen de nieuwe en de vorige ronde moet de dmg opnieuw worden berekend
        {
            PreItemDefDmg=DefDmg*(150-AttDef)/100;
        }
    }
    TempAttDmg=PreItemAttDmg;
    TempDefDmg=PreItemDefDmg;
    itemAttEffectAttacker(ui->AttItem->itemData(ui->AttItem->currentIndex()));
    itemAttEffectDefender(ui->DefItem->itemData(ui->DefItem->currentIndex()));
}
void MainWindow::calcHealth()
{
    QVariant AttCurse=ui->AttCurse->itemData(ui->AttCurse->currentIndex());
    QVariant DefCurse=ui->DefCurse->itemData(ui->DefCurse->currentIndex());

    if(AttCurse.toString()=="Suffocation")
    {
        AttHealth=AttHealth*0.85;
    }
    if(DefCurse.toString()=="Suffocation")
    {
        DefHealth=DefHealth*0.85;
    }
    itemHealthEffectAttacker(ui->AttItem->itemData(ui->AttItem->currentIndex()));
    itemHealthEffectDefender(ui->DefItem->itemData(ui->DefItem->currentIndex()));
}
void MainWindow::itemDefEffectAttacker(QVariant Item)
{
    if(Item.toString()=="Abyss Leech")
    {
        AttDef=AttDef+5;
        AttDefChange=AttDefChange+5;
        DefDef=DefDef-10;
        DefDefChange=DefDefChange-10;
        if(DefDef<0)
        {
            DefDef=0;
        }
        if(AttDef>140)
        {
            AttDef=140;
        }
    }
    else if(Item.toString()=="Styx Cry")
    {
        DefDef=DefDef-13;
        DefDefChange=DefDefChange-13;
        if(DefDef<0)
        {
            DefDef=0;
        }
    } //air draugr items
    else if(Item.toString()=="Corrupted Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            DefDef=getDefDefender("Earth");
            DefDef=DefDef+DefDefChange;
            if(DefDef>140)
            {
                DefDef=140;
            }
            if(DefDef<0)
            {
                DefDef=0;
            }
        }
    }
    else if(Item.toString()=="Leprous Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            DefDef=getDefDefender("Death");
            DefDef=DefDef+DefDefChange;
            if(DefDef>140)
            {
                DefDef=140;
            }
            if(DefDef<0)
            {
                DefDef=0;
            }
        }
    } //forest draugr items
    else if(Item.toString()=="Spectral Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            DefDef=getDefDefender("Air");
            DefDef=DefDef+DefDefChange;
            if(DefDef>140)
            {
                DefDef=140;
            }
            if(DefDef<0)
            {
                DefDef=0;
            }
        }
    }
    else if(Item.toString()=="Acidic Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            DefDef=getDefDefender("Death");
            DefDef=DefDef+DefDefChange;
            if(DefDef>140)
            {
                DefDef=140;
            }
            if(DefDef<0)
            {
                DefDef=0;
            }
        }
    } //death draugr items
    else if(Item.toString()=="Massive Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            DefDef=getDefDefender("Earth");
            DefDef=DefDef+DefDefChange;
            if(DefDef>140)
            {
                DefDef=140;
            }
            if(DefDef<0)
            {
                DefDef=0;
            }
        }
    }
    else if(Item.toString()=="Contorted Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            DefDef=getDefDefender("Forest");
            DefDef=DefDef+DefDefChange;
            if(DefDef>140)
            {
                DefDef=140;
            }
            if(DefDef<0)
            {
                DefDef=0;
            }
        }
    }
}
void MainWindow::itemDefEffectDefender(QVariant Item)
{
    if(Item.toString()=="Abyss Leech")
    {
        DefDef=DefDef+5;
        DefDefChange=DefDefChange+5;
        AttDef=AttDef-10;
        AttDefChange=AttDefChange-10;
        if(AttDef<0)
        {
            AttDef=0;
        }
        if(DefDef>140)
        {
            DefDef=140;
        }
    }
    else if(Item.toString()=="Styx Cry")
    {
        AttDef=AttDef-13;
        AttDefChange=AttDefChange-13;
        if(AttDef<0)
        {
            AttDef=0;
        }
    } //air draugr items
    else if(Item.toString()=="Corrupted Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            AttDef=getDefAttacker("Earth");
            AttDef=AttDef+AttDefChange;
            if(AttDef>140)
            {
                AttDef=140;
            }
            if(AttDef<0)
            {
                AttDef=0;
            }
        }
    }
    else if(Item.toString()=="Leprous Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            AttDef=getDefAttacker("Death");
            AttDef=AttDef+AttDefChange;
            if(AttDef>140)
            {
                AttDef=140;
            }
            if(AttDef<0)
            {
                AttDef=0;
            }
        }
    } //forest draugr items
    else if(Item.toString()=="Spectral Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            AttDef=getDefAttacker("Air");
            AttDef=AttDef+AttDefChange;
            if(AttDef>140)
            {
                AttDef=140;
            }
            if(AttDef<0)
            {
                AttDef=0;
            }
        }
    }
    else if(Item.toString()=="Acidic Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            AttDef=getDefAttacker("Death");
            AttDef=AttDef+AttDefChange;
            if(AttDef>140)
            {
                AttDef=140;
            }
            if(AttDef<0)
            {
                AttDef=0;
            }
        }
    } //death draugr items
    else if(Item.toString()=="Massive Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            AttDef=getDefAttacker("Earth");
            AttDef=AttDef+AttDefChange;
            if(AttDef>140)
            {
                AttDef=140;
            }
            if(AttDef<0)
            {
                AttDef=0;
            }
        }
    }
    else if(Item.toString()=="Contorted Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            AttDef=getDefAttacker("Forest");
            AttDef=AttDef+AttDefChange;
            if(AttDef>140)
            {
                AttDef=140;
            }
            if(AttDef<0)
            {
                AttDef=0;
            }
        }
    }
}
void MainWindow::itemAttEffectAttacker(QVariant Item)
{
    if(Item.toString()=="Tormenter Touch")
    {
        TempDefDmg=PreItemDefDmg-(92*teller);
        if(TempDefDmg<=0)
        {
            TempDefDmg=1;
        }
    }
    else if(Item.toString()=="Leprous Seax" || Item.toString()=="Corrupted Seax" || Item.toString()=="Massive Seax"
            || Item.toString()=="Contorted Seax" || Item.toString()=="Spectral Seax" || Item.toString()=="Acidic Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            PreItemDefDmg=PreItemDefDmg*0.9;
            TempDefDmg=PreItemDefDmg;
        }
    }
    else if(Item.toString()=="Silver Jewel")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            TempAttDmg=PreItemAttDmg+PreItemDefDmg;
        }
    }
    else if(Item.toString()=="Collar of Excellence")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<37)
        {
            TempDefDmg=0;
        }
    }
}
void MainWindow::itemAttEffectDefender(QVariant Item)
{
    if(Item.toString()=="Tormenter Touch")
    {
        TempAttDmg=TempAttDmg-(92*teller);
        if(TempAttDmg<=0)
        {
            TempAttDmg=1;
        }
    }
    else if(Item.toString()=="Leprous Seax" || Item.toString()=="Corrupted Seax" || Item.toString()=="Massive Seax"
            || Item.toString()=="Contorted Seax" || Item.toString()=="Spectral Seax" || Item.toString()=="Acidic Seax")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            PreItemAttDmg=PreItemAttDmg*0.9;
            TempAttDmg=PreItemAttDmg;
        }
    }
    else if(Item.toString()=="Silver Jewel")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<41)
        {
            TempDefDmg=PreItemDefDmg+PreItemAttDmg;
            TempAttDmg=PreItemAttDmg;
        }
    }
}
void MainWindow::itemHealthEffectAttacker(QVariant Item)
{
    if(Item.toString()=="Ancient Heart")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<81)
        {
            AttHealth=AttHealth+380;
        }
    }
    else if(Item.toString()=="Diamond Charm")
    {
        AttHealth=AttHealth+120;
        DefHealth=DefHealth-120;
        if(DefHealth<0)
        {
            DefHealth=0;
        }
    }
}
void MainWindow::itemHealthEffectDefender(QVariant Item)
{
    if(Item.toString()=="Ancient Heart")
    {
        double random = qrand() % ((100+1) - 0)+0;
        if(random<81)
        {
            DefHealth=DefHealth+380;
        }
    }
    else if(Item.toString()=="Diamond Charm")
    {
        AttHealth=AttHealth-120;
        if(AttHealth<0)
        {
            AttHealth=0;
        }
        DefHealth=DefHealth+120;
    }
}
void MainWindow::battle()
{

    if(TempAttDmg<=0) TempAttDmg=1;
    if(TempDefDmg<=0) TempDefDmg=1;

    DefHealth=DefHealth-TempAttDmg;
    AttHealth=AttHealth-TempDefDmg;

    if(DefHealth<0)
    {
        DefHealth=0;
    }
    if(AttHealth<0)
    {
        AttHealth=0;
    }
    ui->Result->append("Attacker did " + QString::number(TempAttDmg) + " and defender has " + QString::number(DefHealth) + " health left.");
    ui->Result->append("Defender did " + QString::number(TempDefDmg) + " and attacker has " + QString::number(AttHealth) + " health left.");

}
