#include "lib.hpp"
#include "Types.hpp"

HOOK_DEFINE_TRAMPOLINE(InitMdataMgr) {

    /* Define the callback for when the function is called. Don't forget to make it static and name it Callback. */
    static void Callback(u64 a1) {

        namespace patch = exl::patch;
        namespace inst = exl::armv8::inst;
        namespace reg = exl::armv8::reg;

        auto& alist = *(prj::list<prj::string>*)(exl::util::modules::GetTargetOffset(0xcb8580));
        prj::string a = "xpack_";
        alist.push_back(a);

        patch::CodePatcher p(0x41b05c);
        p.WriteInst(inst::CmpImmediate(reg::X27, (u16)0x1a));
        Orig(a1);
    }

};

extern "C" void exl_main(void* x0, void* x1) {
    //envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();
    InitMdataMgr::InstallAtOffset(0x41aec0);
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}