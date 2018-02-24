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
struct CountDynamicInstructions : public FunctionPass {
  static char ID;
  CountDynamicInstructions() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {

    Function* udt = cast<Function>(F.getParent()->getOrInsertFunction("updateInstrInfo",
                                                                      Type::getVoidTy(F.getParent()->getContext()),
                                                                      Type::getInt32Ty(F.getParent()->getContext()),
                                                                      Type::getInt32PtrTy(F.getParent()->getContext()),
                                                                      Type::getInt32PtrTy(F.getParent()->getContext())));
    Function* prt = cast<Function>(F.getParent()->getOrInsertFunction("printOutInstrInfo",
                                                                      Type::getVoidTy(F.getParent()->getContext())));
    

    for (Function::iterator B = F.begin(), BE = F.end(); B != BE; ++B) {
      map<int, int> cdi;
      bool flag = false;
      for(BasicBlock::iterator I = B->begin(), IE = B->end(); I != IE; ++I) {
        ++cdi[I->getOpcode()];
        if((string) I->getOpcodeName() == "ret") {
          flag = true;
        }
      }
      int count = cdi.size();
      vector<Constant *> k;
      vector<Constant *> v;
      for(auto &pair : cdi) {
        k.push_back(ConstantInt::get(Type::getInt32Ty(F.getParent()->getContext()), pair.first));
        v.push_back(ConstantInt::get(Type::getInt32Ty(F.getParent()->getContext()), pair.second));
      }

      GlobalVariable* KG = new GlobalVariable(*(F.getParent()),
                                             ArrayType::get(Type::getInt32Ty(F.getParent()->getContext()), count),
                                             true,
                                             GlobalValue::InternalLinkage,
                                             ConstantArray::get(ArrayType::get(Type::getInt32Ty(F.getParent()->getContext()), count), k),
                                             "keys global");
      GlobalVariable* VG = new GlobalVariable(*(F.getParent()),
                                             ArrayType::get(Type::getInt32Ty(F.getParent()->getContext()), count),
                                             true,
                                             GlobalValue::InternalLinkage,
                                             ConstantArray::get(ArrayType::get(Type::getInt32Ty(F.getParent()->getContext()), count), v),
                                             "values global");

      vector<Value *> args;
      args.push_back(ConstantInt::get(Type::getInt32Ty(F.getParent()->getContext()), count));
      

      IRBuilder<> Builder(&*B);
      Builder.SetInsertPoint(B->getTerminator());

      args.push_back(Builder.CreatePointerCast(KG, Type::getInt32PtrTy(F.getParent()->getContext())));
      args.push_back(Builder.CreatePointerCast(VG, Type::getInt32PtrTy(F.getParent()->getContext())));

      Builder.CreateCall(udt, args);

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

char CountDynamicInstructions::ID = 0;
static RegisterPass<CountDynamicInstructions> X("cse231-cdi", "Collecting Dynamic Instruction Counts",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);
