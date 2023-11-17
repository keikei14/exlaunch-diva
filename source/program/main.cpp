#include "lib.hpp"
#include <string>
#include <vector>
#include <cstdlib>

void* (*customNew)(size_t) = reinterpret_cast<void*(*)(size_t)>(exl::util::modules::GetTargetStart() + 0x9f87c0);
void (*customDelete)(void*) = reinterpret_cast<void(*)(void*)>(exl::util::modules::GetTargetStart() + 0x9f87a0);

void* operator new(size_t size) {
    void* ptr = customNew(size);
    return ptr;
}

void operator delete(void* ptr) noexcept {
    customDelete(ptr);
}

HOOK_DEFINE_TRAMPOLINE(InitMdataMgr) {
    /* Define the callback for when the function is called. Don't forget to make it static and name it Callback. */
    static void Callback(u64 a1) {
        Orig(a1);
    }

};

void mainPatch() {

    namespace patch = exl::patch;
    namespace inst = exl::armv8::inst;
    namespace reg = exl::armv8::reg;

    std::vector<std::string*> *stringPointers = new std::vector<std::string*>;

    stringPointers->push_back(new std::string("mdata_"));
    stringPointers->push_back(new std::string("end_"));
    stringPointers->push_back(new std::string("patch_"));
    stringPointers->push_back(new std::string("patch2_"));
    stringPointers->push_back(new std::string("dlc_patch_"));
    stringPointers->push_back(new std::string("dlc1_"));
    stringPointers->push_back(new std::string("dlc2A_"));
    stringPointers->push_back(new std::string("dlc2B_"));
    stringPointers->push_back(new std::string("dlc3A_"));
    stringPointers->push_back(new std::string("dlc3B_"));
    stringPointers->push_back(new std::string("dlc4_"));
    stringPointers->push_back(new std::string("privilege_"));
    stringPointers->push_back(new std::string("dlc7_"));
    stringPointers->push_back(new std::string("dlc8_"));
    stringPointers->push_back(new std::string("dlc9_"));
    stringPointers->push_back(new std::string("dlc10_"));
    stringPointers->push_back(new std::string("dlc11_"));
    stringPointers->push_back(new std::string("dlc12_"));
    stringPointers->push_back(new std::string("dlc13_"));
    stringPointers->push_back(new std::string("dlc14_"));
    stringPointers->push_back(new std::string("dlc15_"));
    stringPointers->push_back(new std::string("dlc16_"));
    stringPointers->push_back(new std::string("dlc17_"));
    stringPointers->push_back(new std::string("dlc18_"));
    stringPointers->push_back(new std::string("dlc19_"));
    stringPointers->push_back(new std::string("xpack_"));

    patch::CodePatcher p(0x41af38);
    p.WriteInst(inst::Adr(reg::X25, (uintptr_t)&stringPointers));
    p.Seek(0x41af3c);
    p.WriteInst(inst::Nop());
    p.Seek(0x41b05c);
    p.WriteInst(inst::CmpImmediate(reg::X27, stringPointers->size()));
}

extern "C" void exl_main(void* x0, void* x1) {
    exl::hook::Initialize();

    mainPatch();
    //InitMdataMgr::InstallAtOffset(0x41aec0);
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}