#include "database.h"

Database::Database()
{

}

bool Database::LoadData(QSqlDatabase *db)
{
    if(db->open())
    {

        mod_1.clear();
        mod_2.clear();
        mod_comp_1.clear();
        mod_comp_2.clear();
        competence_1.clear();
        competence_2.clear();
        conf.clear();
        question.clear();
        discipline_1.clear();
        discipline_2.clear();

        QSqlQuery query;
        query.exec("select module.id_module, module.name_module, module.hours_module, discipline.name_discipline from module, discipline where discipline.id_discipline = module.id_discipline group by module.id_module;");

        if(!query.size())
            return false;

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

        if(!query.size())
            return false;

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

        if(!query.size())
            return false;

        while (query.next())
        {
            temp_MC.id_module = query.value(0).toString();
            temp_MC.id_competence = query.value(1).toString();

            mod_comp_1.push_back(temp_MC);

            qDebug() << query.value(0).toString() << query.value(1).toString();
        }

        query.exec("select * from mod_comp_2;");

        if(!query.size())
            return false;

        while (query.next())
        {
            temp_MC.id_module = query.value(0).toString();
            temp_MC.id_competence = query.value(1).toString();

            mod_comp_2.push_back(temp_MC);

            qDebug() << query.value(0).toString() << query.value(1).toString();
        }



        Conformity temp_conf;

        query.exec("select id_compet, id_compet_2, value_coeff from conformity;");

        if(!query.size())
            return false;

        while (query.next())
        {
            temp_conf.compet_1 = query.value(0).toString();
            temp_conf.compet_2 = query.value(1).toString();
            temp_conf.value_coef = query.value(2).toFloat();

            conf.push_back(temp_conf);

            qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toFloat();
        }



        Question temp_quest;

        query.exec("select * from question");

        if(!query.size())
            return false;

        while (query.next())
        {
            temp_quest.id_compet = query.value(1).toString();
            temp_quest.text = query.value(2).toString();
            temp_quest.a = query.value(3).toString();
            temp_quest.b = query.value(4).toString();
            temp_quest.c = query.value(5).toString();
            temp_quest.d = query.value(6).toString();
            temp_quest.answer_true = query.value(7).toString();

            question.push_back(temp_quest);

            qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString() << query.value(5).toString() << query.value(6).toString() << query.value(7).toString();
        }

        Competence temp_compet;

        query.exec("select * from competence");

        while (query.next())
        {
            temp_compet.number = query.value(0).toString();
            temp_compet.name = query.value(1).toString();
            temp_compet.text = query.value(2).toString();

            competence_1.push_back(temp_compet);
        }

        query.exec("select * from competence_2");

        while (query.next())
        {
            temp_compet.number = query.value(0).toString();
            temp_compet.name = query.value(1).toString();
            temp_compet.text = query.value(2).toString();

            competence_2.push_back(temp_compet);
        }

        Discipline temp_disc;

        query.exec("select * from discipline");

        while (query.next())
        {
            temp_disc.id = query.value(0).toString();
            temp_disc.name = query.value(1).toString();
            temp_disc.control = query.value(2).toString();

            discipline_1.push_back(temp_disc);
        }        

        query.exec("select * from discipline_2");

        while (query.next())
        {
            temp_disc.id = query.value(0).toString();
            temp_disc.name = query.value(1).toString();
            temp_disc.control = query.value(2).toString();

            discipline_2.push_back(temp_disc);
        }

        return true;
    }
    else
        return false;

}

void Database::Calculate(int hours_full, float coef)
{
    result_mod.clear();
    result_question.clear();

    for(int i = 0; i < conf.size()-1; i++)
        for(int j = i; j < conf.size(); j++)
            if(conf[i].value_coef < conf[j].value_coef)
                swap(conf[i], conf[j]);

    qDebug() << "First sort complete!";

    for(int i = 0; i < conf.size(); i++)
        qDebug() << conf[i].compet_1 << conf[i].value_coef;

    for(int i = 0; i < mod_1.size()-1; i++)
        for(int j = i+1; j < mod_1.size(); j++)
        {
            int number_i;
            int number_j;

            for(int z = 0; z < mod_comp_1.size(); z++)
            {
                if(mod_1[i].id == mod_comp_1[z].id_module)
                {
                    for(int x = 0; x < conf.size(); x++)
                    {
                        if(mod_comp_1[z].id_competence == conf[x].compet_1)
                            number_i = x;
                    }
                }

                if(mod_1[j].id == mod_comp_1[z].id_module)
                {
                    for(int x = 0; x < conf.size(); x++)
                    {
                        if(mod_comp_1[z].id_competence == conf[x].compet_1)
                            number_j = x;
                    }
                }
            }

            if(number_i > number_j)
                swap(mod_1[i], mod_1[j]);
        }

    qDebug() << "Second sort complete!";

    for(int j = 0; j < mod_1.size(); j++)
    {

        for(int z = 0; z < mod_comp_1.size(); z++)
        {
            if(mod_1[j].id == mod_comp_1[z].id_module)
            {
                qDebug() << mod_1[j].id << mod_comp_1[z].id_competence;
            }
        }
    }

    for(int i = 0; i < mod_1.size(); i++)
    {
        float max_coef = 0;
        QString competence;
        int number_z1;
        int number_j1;

        for(int z = 0; z < mod_comp_1.size(); z++)
        {
            if(mod_1[i].id == mod_comp_1[z].id_module)
            {
                for(int j = 0; j < conf.size(); j++)
                {
                    if(mod_comp_1[z].id_competence == conf[j].compet_1)
                    {
                        if(conf[j].value_coef > max_coef)
                        {
                            max_coef = conf[j].value_coef;
                            competence = conf[j].compet_2;
                            number_z1 = z;
                        }
                    }
                }
            }
        }

        qDebug() << "First half calculate complete!" << max_coef << coef;

        if(max_coef >= coef)
        {
            int number_j;
            int number_z;
            int hours = 0;

            for(int j = 0; j < mod_comp_2.size(); j++)
            {
                if(mod_comp_2[j].id_competence == competence)
                {
                    for(int z = 0; z < mod_2.size(); z++)
                    {
                        if(mod_2[z].id == mod_comp_2[j].id_module)
                        {
                            if(mod_2[z].hours > hours)
                            {
                                hours = mod_2[z].hours;
                                number_z = z;
                                number_j = j;
                            }
                        }
                    }
                }
            }

            result_mod.push_back(mod_2[number_z]);


            for(int z = 0; z < mod_comp_2.size(); z++)
            {
                if(mod_2[number_z].id == mod_comp_2[z].id_module)
                {
                    for(int j = 0; j < question.size(); j++)
                    {
                        if(mod_comp_2[z].id_competence == question[j].id_compet)
                            result_question.push_back(question[j]);
                    }
                }
            }


            mod_2.erase(mod_2.begin() + number_z);
            mod_comp_2.erase(mod_comp_2.begin() + number_j);
            mod_comp_1.erase(mod_comp_1.begin() + number_z1);
            mod_1.erase(mod_1.begin() + number_j1);

            hours_full -= hours;
        }

        qDebug() << "Second half calculate complete!";

        if(hours_full <= 0 || max_coef < coef)
            break;
    }

    qDebug() << "Calculate complete!";

    for(int i = 0; i < result_mod.size(); i++)
        qDebug() << result_mod[i].id << result_mod[i].name << result_mod[i].hours << result_mod[i].discipline;
}
