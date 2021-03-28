#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/PassManager.h>
#include <llvm/CodeGen/CommandFlags.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/IR/IRPrintingPasses.h>
#include "llvm/IR/Verifier.h"
#include <llvm/IR/LegacyPassManager.h>

#include "codegen.h"

using namespace llvm;
using namespace std;

struct CodeGen {
	Module *mod;	
	TargetMachine *target_machine;
	const Target *target;
};

static void init(CodeGen *, Module *);
static void write_llir(CodeGen *, Module *, string);
static void write_asm(CodeGen *, Module *, string);
static void write_obj(CodeGen *, Module *, string);

static bool replace(string &, string, string);

void codegen(string input_file, bool emit_llir, bool emit_asm) {
	string llvm_file = input_file;
    string asm_file = input_file;
    string obj_file = input_file;
    LLVMContext ctx;
    Module *mod = new Module(llvm_file, ctx);
	raw_os_ostream stream(std::cout);
	CodeGen *codegen = new CodeGen();

	codegen->mod = mod;

	mod->setSourceFileName(llvm_file);

    replace(llvm_file, ".kry", ".ll");
    replace(asm_file, ".kry", ".s");
    replace(obj_file, ".kry", ".o");

    init(codegen, mod);

    if (emit_llir)
        write_llir(codegen, mod, llvm_file);

	if (verifyModule(*mod, &stream)) {
		cout << "\n";
		cout << "Failed to verify Module!\n";
	} else {
		if (emit_asm)
		   write_asm(codegen, mod, asm_file);
		write_obj(codegen, mod, obj_file);
	}
}

void init(CodeGen *cg, llvm::Module *mod) {
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmPrinters();
    InitializeAllAsmParsers();
    InitializeNativeTarget();

    TargetMachine *target_machine;
    const Target *target;
    Triple triple;
    string error;
    TargetOptions options;
    auto reloc_model = llvm::Optional<llvm::Reloc::Model>();
    CodeGenOpt::Level optimization;

	cg->target = target;
	cg->target_machine = target_machine;
    
    triple.setTriple(sys::getDefaultTargetTriple());
    triple.setArch(Triple::x86_64);

	target = TargetRegistry::lookupTarget(triple.getTriple(), error);
    optimization = CodeGenOpt::None;

    target_machine = target->createTargetMachine(triple.getTriple(),
                                                    sys::getHostCPUName(),
                                                    "",
                                                    options,
                                                    reloc_model,
                                                    CodeModel::Small,
                                                    optimization
                                         );

    mod->setDataLayout(target_machine->createDataLayout());
	mod->setTargetTriple(triple.getTriple());
}

void write_llir(CodeGen *cg, Module *mod, string llvm_file) {
    ofstream filestream;
	filestream.open(llvm_file);
	if (!filestream.is_open()) {
		cerr << "Couldn't open file '" << llvm_file << "'\n";
        exit(EXIT_FAILURE);
	}
	raw_os_ostream ostream(filestream);
	mod->print(ostream, nullptr);
}

void write_asm(CodeGen *cg, Module *mod, string asm_file) {
	legacy::PassManager pm;

	error_code error;
	raw_fd_ostream out(asm_file, error, sys::fs::F_None);

	/*
	cg->target_machine->addPassesToEmitFile(pm, out, nullptr, CGFT_AssemblyFile);
	*/
	pm.run(*mod);
}

void write_obj(CodeGen *cg, Module *mod, string obj_file) {

}

bool replace(string& str, string from, string to) {
    size_t start_pos = str.find(from);
    if(start_pos == string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}
