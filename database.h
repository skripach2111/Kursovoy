#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <QString>
#include <QSqlDatabase>
#include <QtSql>

using namespace std;

struct Module
{
    QString id;
    QString discipline;
    QString name;
    int hours;
};

struct Conformity
{
    QString compet_1;
    QString compet_2;
    float value_coef;
};

struct Mod_Comp
{
    QString id_module;
    QString id_competence;
};

struct Question
{
    QString id_compet;
    QString text;
    QString a, b, c, d;
    QString answer_true;
};

class Database
{
public:
    vector <Module> mod_1;
    vector <Module> mod_2;
    vector <Conformity> conf;
    vector <Mod_Comp> mod_comp_1;
    vector <Mod_Comp> mod_comp_2;
    vector <Question> question;

    vector <Module> result_mod;
    vector <Question> result_question;

    void LoadData(QSqlDatabase *db);
    void Calculate(int hourse, float coef);

    Database();
};

#endif // DATABASE_H
