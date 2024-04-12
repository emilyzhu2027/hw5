#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle_helper(std::string in, const std::string floating, const std::set<std::string>& dict, std::set<std::string>& final_set, int place, int space_left_count, std::string set_letters);
bool is_valid(std::string in, const std::string& floating, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> final_set;
    int count = 0;
    std::string set_letters = "";
    for (int i=0; i < (int)(in.size()); i++){
      if (in[i] == '-'){
        count++;
      }
      else{
        set_letters += in[i];
      }
    }
    wordle_helper(in, floating, dict, final_set, 0, count, set_letters);
    return final_set;

}

void wordle_helper(std::string in, 
    const std::string floating, 
    const std::set<std::string>& dict,
    std::set<std::string>& final_set,
    int place,
    int space_left_count,
    std::string set_letters)
{
    if (place == (int)(in.size())){
        if (is_valid(in, floating, dict)){
            final_set.insert(in);
        }
    }
    else{
      if (in[place] == '-'){
        std::string temp_floating;
        std::string temp = in;
        std::string letters_to_eliminate = floating + set_letters;

        for (int i = 0; i < (int)(letters_to_eliminate.size()); i++){
          size_t index = temp.find(letters_to_eliminate[i]);
          if (index != std::string::npos){
            temp.erase(index, 1);
          }
          else{
            temp_floating += letters_to_eliminate[i];
          }
        }

        if (space_left_count == (int)(temp_floating.size())){
          for (int i=0; i < (int)(temp_floating.size()); i++){
            char next = temp_floating[i];
            in[place] = next;
            wordle_helper(in, floating, dict, final_set, place + 1, space_left_count-1, set_letters);
          }
        }
        else{
          for (int i=0; i < 26; i++){
              char next = 'a' + i;
              in[place] = next;
              wordle_helper(in, floating, dict, final_set, place + 1, space_left_count-1, set_letters);
          }
        }
      }

      else{
        wordle_helper(in, floating, dict, final_set, place + 1, space_left_count, set_letters);
      }
    }
}

bool is_valid(std::string in,
    const std::string& floating, 
    const std::set<std::string>& dict)
{
  if (dict.find(in) == dict.end()){
        return false;
  }

  return true;
}