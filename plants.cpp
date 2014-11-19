#include "plants.h"

plants::plants()
{
    cost = 0;
    life = 0;
    range = 0;
    damage = 0;
    rate = 0;
    splash = 0;
    slow = 0;
    bomb = 0;
    seeding = 0;
    sun = 0;
    need = 0;
}


PeaShooterClass::PeaShooterClass()
{
    cost = 100;
    life = 4;
    range = 9999;
    damage = 1;
    rate = 1.5;
    splash = 0;
    bomb = 0;
    seeding = 7.5;
    sun = 0;
    need = 0;
}


SunFlowerClass::SunFlowerClass()
{
    cost = 50;
    life = 4;
    range = 0;
    damage = 0;
    rate = 24;
    splash = 0;
    slow = 0;
    bomb = 0;
    seeding = 7.5;
    sun = 1;
    need = 0;
}


CherryBombClass::CherryBombClass()
{
    cost = 150;
    life = 9999;
    range = 1;
    damage = 90;
    rate = 1;
    splash = 3;
    slow = 0;
    bomb = 1;
    seeding = 50;
    sun = 0;
    need = 0;
}

WallNutClass::WallNutClass()
{
    cost = 50;
    life = 72;
    range = 0;
    damage = 0;
    rate = 0;
    splash = 0;
    slow = 0;
    bomb = 0;
    seeding = 30;
    sun = 0;
    need = 0;
}

PotatoMineClass::PotatoMineClass()
{
    cost = 25;
    life = 4;
    range = 1;
    damage = 90;
    rate = 15;
    splash = 0;
    slow = 0;
    bomb = 1;
    seeding = 30;
    sun = 0;
    need = 0;
}

SnowPeaClass::SnowPeaClass()
{
    cost = 175;
    life = 4;
    range = 9999;
    damage = 1;
    rate = 1.5;
    splash = 0;
    slow = 1;
    bomb = 0;
    seeding = 7.5;
    sun = 0;
    need = 0;
}

ChomperClass::ChomperClass()
{
    cost = 150;
    life = 4;
    range = 1;
    damage = 150;
    rate = 42;
    splash = 0;
    slow = 0;
    bomb = 0;
    seeding = 7.5;
    sun = 0;
    need = 0;
}

RepeaterClass::RepeaterClass()
{
    cost = 200;
    life = 4;
    range = 9999;
    damage = 2;
    rate = 1.5;
    splash = 0;
    slow = 0;
    bomb = 0;
    seeding = 7.5;
    sun = 0;
    need = 1;
}
