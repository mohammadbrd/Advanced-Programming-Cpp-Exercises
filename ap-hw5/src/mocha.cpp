#include "mocha.h"
#include "sub_ingredients.h"

//////////////////////////////////////////////////////////
Mocha::Mocha()
{
    side_items.clear();
    name = "Mocha";
    ingredients.push_back(new Espresso{2});
    ingredients.push_back(new Milk{2});
    ingredients.push_back(new MilkFoam{1});
    ingredients.push_back(new Chocolate{1});
}
//////////////////////////////////////////////////////////
Mocha::Mocha(const Mocha& cap)
    :EspressoBased{ cap }
{
    for (Ingredient* component : cap.side_items)
    {
        if(component->get_name() == "Cinnamon")
        {
            side_items.push_back(new Cinnamon{ component->get_units() });
        }
        else if(component->get_name() == "Chocolate")
        {
            side_items.push_back(new Chocolate{ component->get_units() });
        }
        else if(component->get_name() == "Sugar")
        {
            side_items.push_back(new Sugar{ component->get_units() });
        }
        else if(component->get_name() == "Cookie")
        {
            side_items.push_back(new Cookie{ component->get_units() });
        }
        else if(component->get_name() == "Espresso")
        {
            side_items.push_back(new Espresso{ component->get_units() });
        }
        else if(component->get_name() == "Milk")
        {
            side_items.push_back(new Milk{ component->get_units() });
        }
        else if(component->get_name() == "MilkFoam")
        {
            side_items.push_back(new MilkFoam{ component->get_units() });
        }
        else if(component->get_name() == "Water")
        {
            side_items.push_back(new Water{ component->get_units() });
        }

    }
};
//////////////////////////////////////////////////////////
void Mocha::operator=(const Mocha& cap)
{
    if(this == &cap)
    {
        return;
    }

    side_items.clear();

    for (Ingredient* component : cap.side_items)
    {
        if(component->get_name() == "Cinnamon")
        {
            side_items.push_back(new Cinnamon{ component->get_units() });
        }
        else if(component->get_name() == "Chocolate")
        {
            side_items.push_back(new Chocolate{ component->get_units() });
        }
        else if(component->get_name() == "Sugar")
        {
            side_items.push_back(new Sugar{ component->get_units() });
        }
        else if(component->get_name() == "Cookie")
        {
            side_items.push_back(new Cookie{ component->get_units() });
        }
        else if(component->get_name() == "Espresso")
        {
            side_items.push_back(new Espresso{ component->get_units() });
        }
        else if(component->get_name() == "Milk")
        {
            side_items.push_back(new Milk{ component->get_units() });
        }
        else if(component->get_name() == "MilkFoam")
        {
            side_items.push_back(new MilkFoam{ component->get_units() });
        }
        else if(component->get_name() == "Water")
        {
            side_items.push_back(new Water{ component->get_units() });
        }

    }
};
//////////////////////////////////////////////////////////
double Mocha::price()
{
    double pr{0};
    for(const auto& i : ingredients)
        pr += i->price();
    for(const auto& i : side_items)
        pr += i->price();
    return pr;
}
//////////////////////////////////////////////////////////
std::string Mocha::get_name()
{   
    return name;
}
//////////////////////////////////////////////////////////
void Mocha::add_side_item(Ingredient* side)
{   
    side_items.push_back(side);
}
//////////////////////////////////////////////////////////
std::vector<Ingredient*>& Mocha::get_side_items()
{
    return side_items;
}
//////////////////////////////////////////////////////////
Mocha::~Mocha()
{
    for(const auto& i : side_items)
        delete i;
    side_items.clear();
}