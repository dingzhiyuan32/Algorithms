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
struct BranchBias : public FunctionPass {
  static char ID;
  BranchBias() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {

    Module* mod = F.getParent();
    LLVMContext &context = mod->getContext();

    Function* udt = cast<Function>(mod->getOrInsertFunction("updateBranchInfo",
                                                            Type::getVoidTy(context),
                                                            Type::getInt1Ty(context)));
    Function* prt = cast<Function>(mod->getOrInsertFunction("printOutBranchInfo",
                                                            Type::getVoidTy(context)));
    

    for (Function::iterator B = F.begin(), BE = F.end(); B != BE; ++B) {
      
      bool flag = false;
      for(BasicBlock::iterator I = B->begin(), IE = B->end(); I != IE; ++I) {
        //BranchInst* branch = dyn_cast<BranchInst>(&*I);
        if((*I).getOpcode() == 2 && (*I).getNumOperands() > 1) {
          vector<Value *> args;
          args.push_back((*I).getOperand(0));
          IRBuilder<> Builder(&*I);
          Builder.CreateCall(udt, args);
        }
        
        if((string) I->getOpcodeName() == "ret")
          flag = true;
      }
      

      if(flag) {
        BasicBlock::iterator I = B->end();
        I--;
        IRBuilder<> Builder2(&*I);
        Builder2.CreateCall(prt);
      }
      
                                             
    }

    
    return false;
  }
}; // end of struct TestPass
}  // end of anonymous namespace

char BranchBias::ID = 0;
static RegisterPass<BranchBias> X("cse231-bb", "Profiling Branch Bias",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);
