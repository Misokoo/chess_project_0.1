#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/square.h"



string
Square::to_string() const
{
  return this->coord_name;
}

string
Square::coord_to_string() const
{
  string pa1 = "(";
  string pa2 = ")";
  string virgule = ",";
  string my_coord {pa1+ std::to_string(invert_posx(this->coord[0]))+virgule+
    std::to_string(this->coord[1])+pa2 };
  return my_coord;
}

const size_t*
Square::get_coord() const
{
  return this->coord;
}

void
Square::set_square(Square new_square)
{
  this->coord_name = new_square.to_string();
  this->coord[0] = new_square.get_coord()[0];
  this->coord[1] = new_square.get_coord()[1];
}

void
Square:: set_coord(size_t value, size_t idx)
{
  this->coord[idx] = value;
}

///////////////////////fonctions pas dans la classe ////////////////////////////
size_t
invert_posx(size_t _cordx)
{
  return (7 - _cordx);
}


bool
saisie_correcte(string const & cmd)
{
  regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
  if(!regex_match(cmd,mouvmtpattern))
  {
    cout << "saisie incorrect" << endl;
  }
  return regex_match(cmd,mouvmtpattern);
}