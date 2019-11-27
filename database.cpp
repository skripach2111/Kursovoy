#include "database.h"

Database::Database()
{

}

void Database::LoadData(QSqlDatabase *db)
{
    db->open();

    QSqlQuery query;
    query.exec("select module.id_module, module.name_module, module.hours_module, discipline.name_discipline from module, discipline where discipline.id_discipline = module.id_discipline group by module.id_module;");

    Module temp;

    while (query.next())
    {
        temp.id = query.value(0).toString();
        temp.name = query.value(1).toString();
        temp.hours = query.value(2).toInt();
        temp.discipline = query.value(3).toString();

        mod_1.push_back(temp);

        qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toInt() << query.value(3).toString();
    }

    query.exec("select module_2.id_module_2, module_2.name_module_2, module_2.hours_module_2, discipline_2.name_discipline_2 from module_2, discipline_2 where discipline_2.id_discipline_2 = module_2.id_discipline_2 group by module_2.id_module_2;");

    while (query.next())
    {
        temp.id = query.value(0).toString();
        temp.name = query.value(1).toString();
        temp.hours = query.value(2).toInt();
        temp.discipline = query.value(3).toString();

        mod_2.push_back(temp);

        qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toInt() << query.value(3).toString();
    }



    Mod_Comp temp_MC;

    query.exec("select * from mod_comp;");

    while (query.next())
    {
        temp_MC.id_module = query.value(0).toString();
        temp_MC.id_competence = query.value(1).toString();

        mod_comp_1.push_back(temp_MC);

        qDebug() << query.value(0).toString() << query.value(1).toString();
    }

    query.exec("select * from mod_comp_2;");

    while (query.next())
    {
        temp_MC.id_module = query.value(0).toString();
        temp_MC.id_competence = query.value(1).toString();

        mod_comp_2.push_back(temp_MC);

        qDebug() << query.value(0).toString() << query.value(1).toString();
    }



    Conformity temp_conf;

    query.exec("select id_compet, id_compet_2, value_coeff from conformity;");

    while (query.next())
    {
        temp_conf.compet_1 = query.value(0).toString();
        temp_conf.compet_2 = query.value(1).toString();
        temp_conf.value_coef = query.value(2).toFloat();

        conf.push_back(temp_conf);

        qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toFloat();
    }
}

void Database::Calculate(int hourse, float coef)
{
    for(int i = 0; i < conf.size()-1; i++)
        for(int j = i; j < conf.size(); j++)
            if(conf[i].value_coef < conf[j].value_coef)
                swap(conf[i], conf[j]);

    int min_coef = 1;

    for(int i = 0; i < conf.size(); i++)
    {
        if(conf[i].value_coef == min_coef)
        {
            //result_mod.push_back(conf[i]);
        }
    }
}
