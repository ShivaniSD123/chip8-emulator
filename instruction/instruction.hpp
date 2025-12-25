#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <variant>

#include "ADD.hpp"
#include "AND.hpp"
#include "BCD_STORE.hpp"
#include "CALL_SUB.hpp"
#include "CLS.hpp"
#include "DRW_SPRITE.hpp"
#include "FT_SPT_ADDR.hpp"
#include "GET_DELAY_TIMER.hpp"
#include "IND_ASSIGN.hpp"
#include "IND_INC.hpp"
#include "JMP_ADDR.hpp"
#include "JMP_REG.hpp"
#include "LD_REG_MEM.hpp"
#include "OR.hpp"
#include "REG_ASSIGN.hpp"
#include "REG_VAL_ASSIGN.hpp"
#include "REG_VAL_INC.hpp"
#include "Return.hpp"
#include "SET_DELAY_TIMER.hpp"
#include "SET_SOUND_TIMER.hpp"
#include "SHL.hpp"
#include "SHR.hpp"
#include "SKP_IF_EQUALS.hpp"
#include "SKP_KEY_NOT_PRESS.hpp"
#include "SKP_KEY_PRESS.hpp"
#include "SKP_NOT_EQUALS.hpp"
#include "SKP_REG_EQUALS.hpp"
#include "SKP_REG_NOT_EQUALS.hpp"
#include "STR_REG_MEM.hpp"
#include "SUB.hpp"
#include "SUBN.hpp"
#include "Unknown.hpp"
#include "WT_KEY_PRESS.hpp"
#include "XOR.hpp"

struct Instruction
    : public std::variant<
          Return, CLS, Unknown, JMP_ADDR, CALL_SUB, JMP_REG, SKP_IF_EQUALS,
          SKP_NOT_EQUALS, SKP_REG_EQUALS, SKP_REG_NOT_EQUALS, REG_VAL_ASSIGN,
          REG_VAL_INC, REG_ASSIGN, OR, AND, XOR, ADD, SUB, SHR, SUBN, SHL,
          IND_ASSIGN, IND_INC, FT_SPT_ADDR, BCD_STORE, STR_REG_MEM, LD_REG_MEM,
          DRW_SPRITE, SKP_KEY_PRESS, SKP_KEY_NOT_PRESS, GET_DELAY_TIMER,
          WT_KEY_PRESS, SET_DELAY_TIMER, SET_SOUND_TIMER> {
  std::string str() const {
    return std::visit([](auto r) { return r.str(); }, *this);
  }
};

Instruction parse_instruction_bits(uint16_t bits) {
  if (bits == 0x00ee)
    return Instruction{Return{}};
  else if (bits == 0x00e0)
    return Instruction{CLS{}};
  else if ((bits & 0xf000) == 0x1000) {
    return Instruction{JMP_ADDR{bits & 0x0fff}};
  } else if ((bits & 0xf000) == 0x2000)
    return Instruction{CALL_SUB{bits & 0x0fff}};
  else if ((bits & 0xf000) == 0xb000)
    return Instruction{JMP_REG{bits & 0x0fff}};
  else if ((bits & 0xf000) == 0x3000)
    return Instruction{SKP_IF_EQUALS{bits & 0x0f00, bits & 0x00ff}};
  else if ((bits & 0xf000) == 0x4000)
    return Instruction{SKP_NOT_EQUALS{bits & 0x0f00, bits & 0x00ff}};
  else if ((bits & 0xf00f) == 0x5000)
    return Instruction{SKP_REG_EQUALS{bits & 0x0f00, bits & 0x00f0}};
  else if ((bits & 0xf00f) == 0x9000)
    return Instruction{SKP_REG_NOT_EQUALS{bits & 0x0f00, bits & 0x00f0}};
  else if ((bits & 0xf000) == 0x6000)
    return Instruction{REG_VAL_ASSIGN{bits & 0x0f00, (bits & 0x00ff)}};
  else if ((bits & 0xf000) == 0x7000)
    return Instruction{REG_VAL_INC{bits & 0x0f00, bits & 0x00ff}};
  else if ((bits & 0xf000) == 0x8000)
    return Instruction{REG_ASSIGN{bits & 0x0f00, bits & 0x00f0}};
  else if ((bits & 0xf00f) == 0x8001)
    return Instruction{OR{bits & 0x0f00, bits & 0x00f0}};
  else if ((bits & 0xf00f) == 0x8002)
    return Instruction{AND{bits & 0x0f00, bits & 0x00f0}};
  else if ((bits & 0xf00f) == 0x8003)
    return Instruction{XOR{bits & 0x0f00, bits & 0x00f0}};
  else if ((bits & 0xf00f) == 0x8004)
    return Instruction{ADD{bits & 0x0f00, bits & 0x00f0}};
  else if ((bits & 0xf00f) == 0x8005)
    return Instruction{SUB{bits & 0x0f00, bits & 0x00f0}};
  else if ((bits & 0xf00f) == 0x8006)
    return Instruction{SHR{bits & 0x0f00, bits & 0x00f0}};
  else if ((bits & 0xf00f) == 0x8007)
    return Instruction{SUBN{bits & 0x0f00, bits & 0x00f0}};
  else if ((bits & 0xf00f) == 0x800e)
    return Instruction{SHL{bits & 0x0f00, bits & 0x00f0}};
  else if ((bits & 0xf000) == 0xA000)
    return Instruction{IND_ASSIGN{bits & 0x0fff}};
  else if ((bits & 0xf0ff) == 0xA01e)
    return Instruction{IND_INC{bits & 0x0f00}};
  else if ((bits & 0xf0ff) == 0xf029)
    return Instruction{FT_SPT_ADDR{bits & 0xf0ff}};
  else if ((bits & 0xf0ff) == 0xf033)
    return Instruction{BCD_STORE{bits & 0x0f00}};
  else if ((bits & 0xf0ff) == 0xf055)
    return Instruction{STR_REG_MEM{bits & 0x0f00}};
  else if ((bits & 0xf0ff) == 0xd000)
    return Instruction{DRW_SPRITE{bits & 0x0f00, bits & 0x00f0, bits & 0x000f}};
  else if ((bits & 0xf000) == 0xf065)
    return Instruction{LD_REG_MEM{bits & 0x0f00}};
  else if ((bits & 0xf0ff) == 0xe09e)
    return Instruction{SKP_KEY_PRESS{bits & 0x0f00}};
  else if ((bits & 0xf0ff) == 0xe0a1)
    return Instruction{SKP_KEY_NOT_PRESS{bits & 0x0f00}};
  else if ((bits & 0xf0ff) == 0xf00a)
    return Instruction{WT_KEY_PRESS{bits & 0x0f00}};
  else if ((bits & 0xf0ff) == 0xf007)
    return Instruction{GET_DELAY_TIMER{bits & 0x0f00}};
  else if ((bits & 0xf0ff) == 0xf0015)
    return Instruction{SET_DELAY_TIMER{bits & 0x0f00}};
  else if ((bits & 0xf0ff) == 0xf018)
    return Instruction{SET_SOUND_TIMER{bits & 0x0f00}};
  else
    return Instruction{Unknown{bits}};
}
