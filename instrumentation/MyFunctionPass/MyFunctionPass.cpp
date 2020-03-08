#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"

using namespace llvm;

namespace {
    class MyFunctionPass : public FunctionPass {
    public:
        static char ID;

        static uint64_t functionID;

        MyFunctionPass() : FunctionPass(ID) {}

        virtual bool runOnFunction(Function &F) { 
            outs() << functionID ++ << "\n";
            outs() << "Hello: ";
            outs().write_escaped(F.getName()) << "\n";
            auto BBBegin = F.begin();
            auto InstBegin = BBBegin->begin();
            IRBuilder<> Builder(BBBegin->getFirstNonPHI());
            std::vector<Type *> argsType;
            auto funcID = ConstantInt::get(Type::getInt64Ty(F.getContext()), functionID);
            argsType.push_back(Type::getInt64Ty(F.getContext()));
            ArrayRef<Type *> argsRef(argsType);
            auto funcType = FunctionType::get(Builder.getVoidTy(), argsRef, false);
            auto M = F.getParent();
            auto recordMallocFunc = M->getOrInsertFunction("__enter_function", funcType);
            Builder.CreateCall(recordMallocFunc, {funcID});
            return false;
        }
    };
}

char MyFunctionPass::ID = 0;
uint64_t MyFunctionPass::functionID = 0;

static RegisterPass<MyFunctionPass> X("myfunction", "My Function Pass");
static void registerPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new MyFunctionPass());
}

static RegisterStandardPasses
    RegisterTheSpindlePass(PassManagerBuilder::EP_EarlyAsPossible, registerPass);
