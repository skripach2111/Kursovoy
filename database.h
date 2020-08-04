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

struct Competence
{
    QString number;
    QString name;
    QString text;
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

struct Discipline
{
    QString id;
    QString name;
    QString control;
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
    vector <Competence> competence_1;
    vector <Competence> competence_2;
    vector <Discipline> discipline_1;
    vector <Discipline> discipline_2;

    vector <Module> result_mod;
    vector <Question> result_question;

    bool LoadData(QSqlDatabase *db);
    void Calculate(int hourse, float coef);
    void SaveOnHostData(QSqlDatabase *db);

    Database();
};

#endif // DATABASE_H
