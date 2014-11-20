#ifndef PLANTS_H
#define PLANTS_H

class plants
{
public:
    plants();
    int setLife();
    int getPlantID();

protected:
    int cost;
    int life;
    int range;
    int damage;
    double rate;
    int splash;
    int slow;
    int bomb;
    double seeding;
    int sun;
    int need;
    int plantID;
};

class PeaShooterClass : public plants
{
public:
    PeaShooterClass();
};

class SunFlowerClass : public plants
{
public:
    SunFlowerClass();
};

class CherryBombClass : public plants
{
public:
    CherryBombClass();
};

class WallNutClass : public plants
{
public:
    WallNutClass();
};

class PotatoMineClass : public plants
{
public:
    PotatoMineClass();
};

class SnowPeaClass : public plants
{
public:
    SnowPeaClass();
};

class ChomperClass : public plants
{
public:
    ChomperClass();
};

class RepeaterClass : public plants
{
public:
    RepeaterClass();
};

#endif // PLANTS_H
