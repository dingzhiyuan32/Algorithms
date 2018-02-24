#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstIterator.h"

#include "llvm/IR/Type.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Value.h"

using namespace llvm;
using namespace std;

namespace {
struct CountStaticInstructions : public FunctionPass {
  static char ID;
  CountStaticInstructions() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    map<string, int> csi;
    for(inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) 
        ++csi[I->getOpcodeName()];
    for(auto &pair : csi)
        errs() << pair.first << "\t" << pair.second << "\n";

    //errs() << "Hello: ";
    //errs().write_escaped(F.getName()) << '\n';
    return false;
  }
}; // end of struct TestPass
}  // end of anonymous namespace

char CountStaticInstructions::ID = 0;
static RegisterPass<CountStaticInstructions> X("cse231-csi", "Collecting Static Instruction Counts",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);
