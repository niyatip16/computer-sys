#include <string>

#include "VMTranslator.h"

using namespace std;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
  // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
  // Your code here
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset) {
  string str = "";
  if (segment == "constant") {
    str = "@" + to_string(offset) + "\n" +
          "D=A\n"
          "@SP\n"
          "A=M\n"
          "M=D\n"
          "@SP\n"
          "M=M+1\n";
  } else if (segment == "local") {
    str = "@" + to_string(offset) + "\n" +
          "D=A\n"
          "@LCL\n"
          "A=M+D\n"
          "D=M\n"
          "@SP\n"
          "A=M\n"
          "M=D\n"
          "@SP\n"
          "M=M+1\n";
  } else if (segment == "argument") {
    str = "@" + to_string(offset) + "\n" +
          "D=A\n"
          "@ARG\n"
          "A=M+D\n"
          "D=M\n"
          "@SP\n"
          "A=M\n"
          "M=D\n"
          "@SP\n"
          "M=M+1\n";
  } else if (segment == "this") {
    str = "@" + to_string(offset) + "\n" +
          "D=A\n"
          "@THIS\n"
          "A=M+D\n"
          "D=M\n"
          "@SP\n"
          "A=M\n"
          "M=D\n"
          "@SP\n"
          "M=M+1\n";
  } else if (segment == "that") {
    str = "@" + to_string(offset) + "\n" +
          "D=A\n"
          "@THAT\n"
          "A=M+D\n"
          "D=M\n"
          "@SP\n"
          "A=M\n"
          "M=D\n"
          "@SP\n"
          "M=M+1\n";
  } else if (segment == "pointer") {
    if (offset == 0) {
      return "@THIS"
             "D=M\n"
             "@SP\n"
             "A=M\n"
             "M=D\n"
             "@SP\n"
             "M=M+1\n";
    } else if (offset == 1) {
      return "@THAT"
             "D=M\n"
             "@SP\n"
             "A=M\n"
             "M=D\n"
             "@SP\n"
             "M=M+1\n";
    }
  } else if (segment == "temp") {
    str = "@R5\n"
          "D=A\n"
          "@" +
          to_string(offset) + "\n" +
          "A=D+A\n"
          "D=M\n"
          "@SP\n"
          "A=M\n"
          "M=D\n"
          "@SP\n"
          "M=M+1\n";
  } else if (segment == "static") {
    str = "@" + to_string(16 + offset) +
          "\n"
          "D=M\n"
          "@SP\n"
          "A=M\n"
          "M=D\n"
          "@SP\n"
          "M=M+1\n";
  }

  return str;
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset) {
  string str = "";
  if (segment == "local") {
    str = "@" + to_string(offset) + "\n" +
          "D=A\n"
          "@LCL\n"
          "D=M+D\n"
          "@R13\n"
          "M=D\n"
          "@SP\n"
          "AM=M-1\n"
          "D=M\n"
          "@R13\n"
          "A=M\n"
          "M=D\n";
  } else if (segment == "argument") {
    str = "@" + to_string(offset) + "\n" +
          "D=A\n"
          "@ARG\n"
          "D=M+D\n"
          "@R13\n"
          "M=D\n"
          "@SP\n"
          "AM=M-1\n"
          "D=M\n"
          "@R13\n"
          "A=M\n"
          "M=D\n";
  } else if (segment == "this") {
    str = "@" + to_string(offset) + "\n" +
          "D=A\n"
          "@THIS\n"
          "D=M+D\n"
          "@R13\n"
          "M=D\n"
          "@SP\n"
          "AM=M-1\n"
          "D=M\n"
          "@R13\n"
          "A=M\n"
          "M=D\n";
  } else if (segment == "that") {
    str = "@" + to_string(offset) + "\n" +
          "D=A\n"
          "@THAT\n"
          "D=M+D\n"
          "@R13\n"
          "M=D\n"
          "@SP\n"
          "AM=M-1\n"
          "D=M\n"
          "@R13\n"
          "A=M\n"
          "M=D\n";
  } else if (segment == "pointer") {
    if (offset == 0) {
      str = "@SP\n"
            "AM=M-1\n"
            "D=M\n"
            "@THIS\n"
            "M=D\n";
    } else if (offset == 1) {
      str = "@SP\n"
            "AM=M-1\n"
            "D=M\n"
            "@THAT\n"
            "M=D\n";
    }
  } else if (segment == "temp") {
    str = "@R5\n"
          "D=A\n"
          "@" +
          to_string(offset) + "\n" +
          "D=D+A\n"
          "@R13\n"
          "M=D\n"
          "@SP\n"
          "AM=M-1\n"
          "D=M\n"
          "@R13\n"
          "A=M\n"
          "M=D\n";
  } else if (segment == "static") {
    str = "@SP\n"
          "AM=M-1\n"
          "D=M\n"
          "@" +
          to_string(16 + offset) +
          "\n"
          "M=D\n";
  }

  return str;
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add() {
  return "@SP\n"
         "AM=M-1\n"
         "D=M\n"
         "A=A-1\n"
         "M=D+M\n";
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub() {
  return "@SP\n"
         "AM=M-1\n"
         "D=M\n"
         "A=A-1\n"
         "M=M-D\n";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg() {
  return "@SP\n"
         "A=M\n"
         "A=A-1\n"
         "M=-M\n";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq() {
  static int eq_counter = 0;
  eq_counter++;

  return "@SP\n"
         "AM=M-1\n"
         "D=M\n"
         "@SP\n"
         "AM=M-1\n"
         "D=M-D\n"
         "@EQ_TRUE_" +
         to_string(eq_counter) +
         "\n"
         "D;JEQ\n"
         "@SP\n"
         "A=M\n"
         "M=0\n"
         "@EQ_FALSE_" +
         to_string(eq_counter) +
         "\n"
         "0;JMP\n"
         "(TRUE)\n"
         "@SP\n"
         "A=M\n"
         "M=-1\n"
         "(FALSE)\n"
         "@SP\n"
         "M=M+1\n";
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt() {
  static int gt_counter = 0;
  gt_counter++;

  return "@SP\n"
         "AM=M-1\n"
         "D=M\n"
         "@SP\n"
         "AM=M-1\n"
         "D=M-D\n"
         "@GT_TRUE_" +
         to_string(gt_counter) +
         "\n"
         "D;JGT\n"
         "@SP\n"
         "A=M\n"
         "M=0\n"
         "@GT_END_" +
         to_string(gt_counter) +
         "\n"
         "0;JMP\n"
         "(GT_TRUE_" +
         to_string(gt_counter) +
         ")\n"
         "@SP\n"
         "A=M\n"
         "M=-1\n"
         "(GT_END_" +
         to_string(gt_counter) +
         ")\n"
         "@SP\n"
         "M=M+1\n";
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt() {
  static int lt_counter = 0;
  lt_counter++;

  return "@SP\n"
         "AM=M-1\n"
         "D=M\n"
         "@SP\n"
         "AM=M-1\n"
         "D=M-D\n"
         "@LT_TRUE_" +
         to_string(lt_counter) +
         "\n"
         "D;JLT\n"
         "@SP\n"
         "A=M\n"
         "M=0\n"
         "@LT_END_" +
         to_string(lt_counter) +
         "\n"
         "0;JMP\n"
         "(LT_TRUE_" +
         to_string(lt_counter) +
         ")\n"
         "@SP\n"
         "A=M\n"
         "M=-1\n"
         "(LT_END_" +
         to_string(lt_counter) +
         ")\n"
         "@SP\n"
         "M=M+1\n";
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and() {
  return "@SP\n"
         "AM=M-1\n"
         "D=M\n"
         "A=A-1\n"
         "M=D&M\n";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or() {
  return "@SP"
         "AM=M-1\n"
         "D=M\n"
         "A=A-1\n"
         "M=D|M\n";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not() {
  return "@SP\n"
         "A=M\n"
         "A=A-1\n"
         "M=!M\n";
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label) {
  return "(" + label +
         ")\n"
         "@" +
         label +
         "\n"
         "0;JMP\n";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label) {
  return "@" + label +
         "\n"
         "D;JMP\n";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label) {
  return "@SP\n"
         "AM=M-1\n"
         "D=M\n"
         "@" +
         label +
         "\n"
         "D;JNE\n";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars) {
  string function;
  function = "(" + function_name + ")\n";

  for (int n = n_vars; n > 0; n--) {
    function += "@SP\n"
                "A=M\n"
                "M=0\n"
                "@SP\n"
                "M=M+1\n";
  }

  return function;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args) {
  static int rtrn_counter = 0;
  rtrn_counter++;

  return "@ADDRESS_" + to_string(rtrn_counter) +
         "\n"
         "D=A\n"
         "@SP\n"
         "A=M\n"
         "M=D\n"
         "@SP\n"
         "M=M+1\n"

         "@LCL\n"
         "D=M\n"
         "@SP\n"
         "A=M\n"
         "M=D\n"
         "@SP\n"
         "M=M+1\n"

         "@ARG\n"
         "D=M\n"
         "@SP\n"
         "A=M\n"
         "M=D\n"
         "@SP\n"
         "M=M+1\n"

         "@THIS\n"
         "D=M\n"
         "@SP\n"
         "A=M\n"
         "M=D\n"
         "@SP\n"
         "M=M+1\n"

         "@THAT\n"
         "D=M\n"
         "@SP\n"
         "A=M\n"
         "M=D\n"
         "@SP\n"
         "M=M+1\n"
         "@SP\n"
         "D=M\n"
         "@5\n"
         "D=D-A\n"
         "@" +
         to_string(n_args) +
         "\n"
         "D=D-A\n"
         "@ARG\n"
         "M=D\n"

         "@SP\n"
         "D=M\n"
         "@LCL\n"
         "M=D\n"

         "@" +
         function_name +
         "\n"
         "0;JMP\n"
         "(ADDRESS_" +
         to_string(rtrn_counter) + ")\n";
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return() {
  return "@LCL\n"
         "D=M\n"
         "@R13\n"
         "M=D\n"
         "@R13\n"
         "D=M\n"
         "@5\n"
         "A=D-A\n"
         "D=M\n"
         "@R14\n"
         "M=D\n"

         "@SP\n"
         "AM=M-1\n"
         "D=M\n"
         "@ARG\n"
         "A=M\n"
         "M=D\n"

         "@ARG\n"
         "D=M+1\n"
         "@SP\n"
         "M=D\n"

         "@R13\n"
         "D=M\n"
         "@1\n"
         "A=D-A\n"
         "D=M\n"
         "@THAT\n"
         "M=D\n"
         "@R13\n"
         "D=M\n"
         "@2\n"
         "A=D-A\n"
         "D=M\n"
         "@THIS\n"
         "M=D\n"

         "@R13\n"
         "D=M\n"
         "@3\n"
         "A=D-A\n"
         "D=M\n"
         "@ARG\n"
         "M=D\n"
         "@R13\n"
         "D=M\n"
         "@4\n"
         "A=D-A\n"
         "D=M\n"
         "@LCL\n"
         "M=D\n"

         "@R14\n"
         "A=M\n"
         "0;JMP\n";
}
