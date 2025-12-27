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
  // ---- extract common fields ----
  uint8_t X = (bits & 0x0F00) >> 8;
  uint8_t Y = (bits & 0x00F0) >> 4;
  uint8_t N = (bits & 0x000F);
  uint8_t NN = (bits & 0x00FF);
  uint16_t NNN = (bits & 0x0FFF);

  // ---- exact matches ----
  if (bits == 0x00E0) return Instruction{CLS{}};
  if (bits == 0x00EE) return Instruction{Return{}};

  // ---- primary opcode group ----
  switch (bits & 0xF000) {
    case 0x1000:
      return Instruction{JMP_ADDR{NNN}};
    case 0x2000:
      return Instruction{CALL_SUB{NNN}};
    case 0x3000:
      return Instruction{SKP_IF_EQUALS{X, NN}};
    case 0x4000:
      return Instruction{SKP_NOT_EQUALS{X, NN}};
    case 0x6000:
      return Instruction{REG_VAL_ASSIGN{X, NN}};
    case 0x7000:
      return Instruction{REG_VAL_INC{X, NN}};
    case 0xA000:
      return Instruction{IND_ASSIGN{NNN}};
    case 0xB000:
      return Instruction{JMP_REG{NNN}};
    case 0xD000:
      return Instruction{DRW_SPRITE{X, Y, N}};
  }

  // ---- arithmetic / logic ----
  switch (bits & 0xF00F) {
    case 0x8000:
      return Instruction{REG_ASSIGN{X, Y}};
    case 0x8001:
      return Instruction{OR{X, Y}};
    case 0x8002:
      return Instruction{AND{X, Y}};
    case 0x8003:
      return Instruction{XOR{X, Y}};
    case 0x8004:
      return Instruction{ADD{X, Y}};
    case 0x8005:
      return Instruction{SUB{X, Y}};
    case 0x8006:
      return Instruction{SHR{X}};
    case 0x8007:
      return Instruction{SUBN{X, Y}};
    case 0x800E:
      return Instruction{SHL{X}};
    case 0x9000:
      return Instruction{SKP_REG_NOT_EQUALS{X, Y}};
  }

  // ---- timers / memory / keyboard ----
  switch (bits & 0xF0FF) {
    case 0xE09E:
      return Instruction{SKP_KEY_PRESS{X}};
    case 0xE0A1:
      return Instruction{SKP_KEY_NOT_PRESS{X}};
    case 0xF007:
      return Instruction{GET_DELAY_TIMER{X}};
    case 0xF00A:
      return Instruction{WT_KEY_PRESS{X}};
    case 0xF015:
      return Instruction{SET_DELAY_TIMER{X}};
    case 0xF018:
      return Instruction{SET_SOUND_TIMER{X}};
    case 0xF01E:
      return Instruction{IND_INC{X}};
    case 0xF029:
      return Instruction{FT_SPT_ADDR{X}};
    case 0xF033:
      return Instruction{BCD_STORE{X}};
    case 0xF055:
      return Instruction{STR_REG_MEM{X}};
    case 0xF065:
      return Instruction{LD_REG_MEM{X}};
  }

  // ---- unknown / SYS ----
  return Instruction{Unknown{bits}};
}
