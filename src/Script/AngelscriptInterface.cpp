#include "AngelscriptInterface.h"
#include "../Math/Vector.h"
#include "../Input.h"
#include "Script.h"
#include "../Components/Transform.h"
#include "../GameObject.h"
#include "../Keycodes.h"

#include <iostream>

namespace glGame {

    template<typename T>
    void print(const T& in) { std::cout << in << std::flush; }
    template<typename T>
    void println(const T& in) { std::cout << in << std::endl; }

    void Vector3DefConstructor(void* memory) { new(memory) Vector3(0, 0, 0); }
    void Vector3Constructor(void* memory, float x, float y, float z) { new(memory) Vector3(x, y, z); }
    void Vector3Destructor(void* memory) { ((Vector3*)memory)->~Vector3(); }
    void Vector3iDefConstructor(void* memory) { new(memory) Vector3i(0, 0, 0); }
    void Vector3iConstructor(void* memory, int x, int y, int z) { new(memory) Vector3i(x, y, z); }
    void Vector3iDestructor(void* memory) { ((Vector3i*)memory)->~Vector3i(); }
    void Vector2DefConstructor(void* memory) { new(memory) Vector2(0, 0); }
    void Vector2Constructor(void* memory, float x, float y) { new(memory) Vector2(x, y); }
    void Vector2Destructor(void* memory) { ((Vector2*)memory)->~Vector2(); }
    void Vector2iDefConstructor(void* memory) { new(memory) Vector2i(0, 0); }
    void Vector2iConstructor(void* memory, int x, int y) { new(memory) Vector2i(x, y); }
    void Vector2iDestructor(void* memory) { ((Vector2i*)memory)->~Vector2i(); }
    void QuaternionConstructor(void* memory, float w, float x, float y, float z) { new(memory) Quaternion(w, x, y, z); }
    void QuaternionDefConstructor(void* memory) { new(memory) Quaternion(); }
    void QuaternionEulerConstructor(void* memory, Vector3 eulerAngles) { new(memory) Quaternion(glm::vec3(eulerAngles.x, eulerAngles.y, eulerAngles.z)); }
    void QuaternionDestructor(void* memory) { ((Quaternion*)memory)->~Quaternion(); }

    void MessageCallback(const asSMessageInfo *msg, void *param) {
        const char *type = "ERR ";
        if( msg->type == asMSGTYPE_WARNING ) 
            type = "WARN";
        else if( msg->type == asMSGTYPE_INFORMATION ) 
            type = "INFO";
        printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
    }

    void AngelscriptInterface::Register(asIScriptEngine* scriptEngine) {
        scriptEngine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

        RegisterStdString(scriptEngine);
        RegisterScriptMath(scriptEngine);

        // Vector2
        scriptEngine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asGetTypeTraits<Vector2>() | asOBJ_APP_CLASS_ALLFLOATS);
        scriptEngine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void Vector2(float x, float y)", asFUNCTION(Vector2Constructor), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void Vector2()", asFUNCTION(Vector2DefConstructor), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectBehaviour("Vector2", asBEHAVE_DESTRUCT, "void Vector2()", asFUNCTION(Vector2Destructor), asCALL_CDECL_OBJLAST);
        scriptEngine->RegisterObjectMethod("Vector2", "Vector2& opAssign(const Vector2& in)", asMETHODPR(Vector2, operator=, (const Vector2&), Vector2&), asCALL_THISCALL);
        scriptEngine->RegisterObjectMethod("Vector2", "Vector2 opAdd(const Vector2& in)", asFUNCTIONPR(glm::operator+, (const Vector2&, const Vector2&), Vector2), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectMethod("Vector2", "Vector2 opSub(const Vector2& in)", asFUNCTIONPR(glm::operator-, (const Vector2&, const Vector2&), Vector2), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectMethod("Vector2", "Vector2 opMul(const Vector2& in)", asFUNCTIONPR(glm::operator*, (const Vector2&, const Vector2&), Vector2), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectMethod("Vector2", "Vector2 opMul(float)", asFUNCTIONPR(glm::operator*, (const Vector2&, float), Vector2), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectProperty("Vector2", "float x", asOFFSET(Vector2, Vector2::x));
        scriptEngine->RegisterObjectProperty("Vector2", "float y", asOFFSET(Vector2, Vector2::y));

        // Vector2i
        scriptEngine->RegisterObjectType("Vector2i", sizeof(Vector2i), asOBJ_VALUE | asGetTypeTraits<Vector2i>() | asOBJ_APP_CLASS_ALLINTS);
        scriptEngine->RegisterObjectBehaviour("Vector2i", asBEHAVE_CONSTRUCT, "void Vector2i(int x, int y)", asFUNCTION(Vector2iConstructor), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectBehaviour("Vector2i", asBEHAVE_CONSTRUCT, "void Vector2i()", asFUNCTION(Vector2iDefConstructor), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectBehaviour("Vector2i", asBEHAVE_DESTRUCT, "void Vector2i()", asFUNCTION(Vector2iDestructor), asCALL_CDECL_OBJLAST);
        scriptEngine->RegisterObjectMethod("Vector2i", "Vector2i& opAssign(const Vector2i& in)", asMETHODPR(Vector2i, operator=, (const Vector2i&), Vector2i&), asCALL_THISCALL);
        scriptEngine->RegisterObjectMethod("Vector2i", "Vector2i opAdd(const Vector2i& in)", asFUNCTIONPR(glm::operator+, (const Vector2i&, const Vector2i&), Vector2i), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectMethod("Vector2i", "Vector2i opSub(const Vector2i& in)", asFUNCTIONPR(glm::operator-, (const Vector2i&, const Vector2i&), Vector2i), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectMethod("Vector2i", "Vector2i opMul(const Vector2i& in)", asFUNCTIONPR(glm::operator*, (const Vector2i&, const Vector2i&), Vector2i), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectMethod("Vector2i", "Vector2i opMul(int)", asFUNCTIONPR(glm::operator*, (const Vector2i&, int), Vector2i), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectProperty("Vector2i", "int x", asOFFSET(Vector2i, Vector2i::x));
        scriptEngine->RegisterObjectProperty("Vector2i", "int y", asOFFSET(Vector2i, Vector2i::y));

        // Vector3
        scriptEngine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_VALUE | asGetTypeTraits<Vector3>() | asOBJ_APP_CLASS_ALLFLOATS);
        scriptEngine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void Vector3(float x, float y, float z)", asFUNCTION(Vector3Constructor), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void Vector3()", asFUNCTION(Vector3DefConstructor), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectBehaviour("Vector3", asBEHAVE_DESTRUCT, "void Vector3()", asFUNCTION(Vector3Destructor), asCALL_CDECL_OBJLAST);
        scriptEngine->RegisterObjectMethod("Vector3", "Vector3& opAssign(const Vector3& in)", asMETHODPR(Vector3, operator=, (const Vector3&), Vector3&), asCALL_THISCALL);
        scriptEngine->RegisterObjectMethod("Vector3", "Vector3 opAdd(const Vector3& in)", asFUNCTIONPR(glm::operator+, (const Vector3&, const Vector3&), Vector3), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectMethod("Vector3", "Vector3 opSub(const Vector3& in)", asFUNCTIONPR(glm::operator-, (const Vector3&, const Vector3&), Vector3), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectMethod("Vector3", "Vector3 opMul(const Vector3& in)", asFUNCTIONPR(glm::operator*, (const Vector3&, const Vector3&), Vector3), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectMethod("Vector3", "Vector3 opMul(float)", asFUNCTIONPR(glm::operator*, (const Vector3&, float), Vector3), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectProperty("Vector3", "float x", asOFFSET(Vector3, Vector3::x));
        scriptEngine->RegisterObjectProperty("Vector3", "float y", asOFFSET(Vector3, Vector3::y));
        scriptEngine->RegisterObjectProperty("Vector3", "float z", asOFFSET(Vector3, Vector3::z));

        // Vector3i
        scriptEngine->RegisterObjectType("Vector3i", sizeof(Vector3i), asOBJ_VALUE | asGetTypeTraits<Vector3i>() | asOBJ_APP_CLASS_ALLFLOATS);
        scriptEngine->RegisterObjectBehaviour("Vector3i", asBEHAVE_CONSTRUCT, "void Vector3i(float x, float y, float z)", asFUNCTION(Vector3iConstructor), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectBehaviour("Vector3i", asBEHAVE_CONSTRUCT, "void Vector3i()", asFUNCTION(Vector3iDefConstructor), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectBehaviour("Vector3i", asBEHAVE_DESTRUCT, "void Vector3i()", asFUNCTION(Vector3iDestructor), asCALL_CDECL_OBJLAST);
        scriptEngine->RegisterObjectMethod("Vector3i", "Vector3i& opAssign(const Vector3i& in)", asMETHODPR(Vector3i, operator=, (const Vector3i&), Vector3i&), asCALL_THISCALL);
        scriptEngine->RegisterObjectMethod("Vector3i", "Vector3i opAdd(const Vector3i& in)", asFUNCTIONPR(glm::operator+, (const Vector3i&, const Vector3i&), Vector3i), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectMethod("Vector3i", "Vector3i opSub(const Vector3i& in)", asFUNCTIONPR(glm::operator-, (const Vector3i&, const Vector3i&), Vector3i), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectMethod("Vector3i", "Vector3i opMul(const Vector3i& in)", asFUNCTIONPR(glm::operator*, (const Vector3i&, const Vector3i&), Vector3i), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectMethod("Vector3i", "Vector3i opMul(int)", asFUNCTIONPR(glm::operator*, (const Vector3i&, int), Vector3i), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectProperty("Vector3i", "float x", asOFFSET(Vector3i, Vector3i::x));
        scriptEngine->RegisterObjectProperty("Vector3i", "float y", asOFFSET(Vector3i, Vector3i::y));
        scriptEngine->RegisterObjectProperty("Vector3i", "float z", asOFFSET(Vector3i, Vector3i::z));

        // Quaternion
        scriptEngine->RegisterObjectType("Quaternion", sizeof(Quaternion), asOBJ_VALUE | asGetTypeTraits<Quaternion>());
        scriptEngine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void Quaternion(float w, float x, float y, float z)", asFUNCTION(QuaternionConstructor), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void Quaternion(Vector3 eulerAngles)", asFUNCTION(QuaternionEulerConstructor), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void Quaternion()", asFUNCTION(QuaternionDefConstructor), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectBehaviour("Quaternion", asBEHAVE_DESTRUCT, "void Quaternion()", asFUNCTION(QuaternionDestructor), asCALL_CDECL_OBJLAST);
        scriptEngine->RegisterObjectMethod("Quaternion", "Quaternion& opAssign(const Quaternion& in)", asMETHODPR(Quaternion, operator=, (const Quaternion&), Quaternion&), asCALL_THISCALL);
        scriptEngine->RegisterObjectMethod("Quaternion", "Vector3 opMul(const Vector3& in)", asFUNCTIONPR(glm::operator*, (const Quaternion&, const Vector3&), Vector3), asCALL_CDECL_OBJFIRST);
        scriptEngine->RegisterObjectProperty("Quaternion", "float w", asOFFSET(Quaternion, Quaternion::w));
        scriptEngine->RegisterObjectProperty("Quaternion", "float x", asOFFSET(Quaternion, Quaternion::x));
        scriptEngine->RegisterObjectProperty("Quaternion", "float y", asOFFSET(Quaternion, Quaternion::y));
        scriptEngine->RegisterObjectProperty("Quaternion", "float z", asOFFSET(Quaternion, Quaternion::z));

        // Transform
        scriptEngine->RegisterObjectType("Transform", sizeof(Transform), asOBJ_REF | asOBJ_NOCOUNT);
        scriptEngine->RegisterObjectMethod("Transform", "void move(const Vector3 &in vector)", asMETHODPR(Transform, Transform::move, (const Vector3&), void), asCALL_THISCALL);
        scriptEngine->RegisterObjectMethod("Transform", "void move(const float &in x, const float &in y, const float &in z)", asMETHODPR(Transform, Transform::move, (const float&, const float&, const float&), void), asCALL_THISCALL);
        scriptEngine->RegisterObjectMethod("Transform", "void rotate(const Vector3 &in vector)", asMETHODPR(Transform, Transform::rotate, (const Vector3&), void), asCALL_THISCALL);
        scriptEngine->RegisterObjectMethod("Transform", "void rotate(const float &in x, const float &in y, const float &in z)", asMETHODPR(Transform, Transform::rotate, (const float&, const float&, const float&), void), asCALL_THISCALL);
        scriptEngine->RegisterObjectMethod("Transform", "Vector3 getEulerAngles()", asMETHOD(Transform, Transform::getEulerAngles), asCALL_THISCALL);
        scriptEngine->RegisterObjectProperty("Transform", "Vector3 position", asOFFSET(Transform, Transform::position));
        scriptEngine->RegisterObjectProperty("Transform", "Vector3 scale", asOFFSET(Transform, Transform::scale));
        scriptEngine->RegisterObjectProperty("Transform", "Quaternion orientation", asOFFSET(Transform, Transform::orientation));
        
        // Print
        scriptEngine->RegisterGlobalFunction("void print(const string &in)", asFUNCTIONPR(print, (const std::string&), void), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("void print(const int &in)", asFUNCTIONPR(print, (const int&), void), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("void print(const float &in)", asFUNCTIONPR(print, (const float&), void), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("void print(const double &in)", asFUNCTIONPR(print, (const double&), void), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("void print(const Vector2 &in)", asFUNCTIONPR(print, (const Vector2&), void), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("void print(const Vector3 &in)", asFUNCTIONPR(print, (const Vector3&), void), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("void println(const string &in)", asFUNCTIONPR(println, (const std::string&), void), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("void println(const int &in)", asFUNCTIONPR(println, (const int&), void), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("void println(const float &in)", asFUNCTIONPR(println, (const float&), void), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("void println(const Vector2 &in)", asFUNCTIONPR(println, (const Vector2&), void), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("void println(const Vector3 &in)", asFUNCTIONPR(println, (const Vector3&), void), asCALL_CDECL);

        // Input
        scriptEngine->RegisterGlobalFunction("bool GetKeyDown(const int &in keycode)", asFUNCTION(Input::GetKeyDown), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("bool GetKeyUp(const int &in keycode)", asFUNCTION(Input::GetKeyUp), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("bool GetKey(const int &in keycode)", asFUNCTION(Input::GetKey), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("Vector2 GetMouseDelta()", asFUNCTION(Input::GetMouseDelta), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("float GetMouseDeltaX()", asFUNCTION(Input::GetMouseDeltaX), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("float GetMouseDeltaY()", asFUNCTION(Input::GetMouseDeltaY), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("bool GetMouseKey(const int &in keycode)", asFUNCTION(Input::GetMouseKey), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("bool GetMouseKeyDown(const int &in keycode)", asFUNCTION(Input::GetMouseKeyDown), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("Vector2 GetMousePosition()", asFUNCTION(Input::GetMousePosition), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("float GetMouseX()", asFUNCTION(Input::GetMouseX), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("float GetMouseY()", asFUNCTION(Input::GetMouseY), asCALL_CDECL);
        scriptEngine->RegisterGlobalFunction("void SetCursorMode(const int &in cursorMode)", asFUNCTION(Input::SetCursorMode), asCALL_CDECL);

        const char* dNamespace = scriptEngine->GetDefaultNamespace();
        scriptEngine->SetDefaultNamespace("KEY");

        const char* keycodeNames[121] = {"const int UNKNOWN", "const int SPACE", "const int APOSTROPHE", "const int COMMA", "const int MINUS", "const int PERIOD", "const int SLASH", "const int NUMBER_0", "const int NUMBER_1", "const int NUMBER_2", "const int NUMBER_3", "const int NUMBER_4", "const int NUMBER_5", "const int NUMBER_6", "const int NUMBER_7", "const int NUMBER_8", "const int NUMBER_9", "const int SEMICOLON", "const int EQUAL", "const int A", "const int B", "const int C", "const int D", "const int E", "const int F", "const int G", "const int H", "const int I", "const int J", "const int K", "const int L", "const int M", "const int N", "const int O", "const int P", "const int Q", "const int R", "const int S", "const int T", "const int U", "const int V", "const int W", "const int X", "const int Y", "const int Z", "const int LEFT_BRACKET", "const int BACKSLASH", "const int RIGHT_BRACKET", "const int GRAVE_ACCENT", "const int WORLD_1", "const int WORLD_2", "const int ESCAPE", "const int ENTER", "const int TAB", "const int BACKSPACE", "const int INSERT", "const int DELETE", "const int RIGHT", "const int LEFT", "const int DOWN", "const int UP", "const int PAGE_UP", "const int PAGE_DOWN", "const int HOME", "const int END", "const int CAPS_LOCK", "const int SCROLL_LOCK", "const int NUM_LOCK", "const int PRINT_SCREEN", "const int PAUSE", "const int F1", "const int F2", "const int F3", "const int F4", "const int F5", "const int F6", "const int F7", "const int F8", "const int F9", "const int F10", "const int F11", "const int F12", "const int F13", "const int F14", "const int F15", "const int F16", "const int F17", "const int F18", "const int F19", "const int F20", "const int F21", "const int F22", "const int F23", "const int F24", "const int F25", "const int KP_0", "const int KP_1", "const int KP_2", "const int KP_3", "const int KP_4", "const int KP_5", "const int KP_6", "const int KP_7", "const int KP_8", "const int KP_9", "const int KP_DECIMAL", "const int KP_DIVIDE", "const int KP_MULTIPLY", "const int KP_SUBTRACT", "const int KP_ADD", "const int KP_ENTER", "const int KP_EQUAL", "const int LEFT_SHIFT", "const int LEFT_CONTROL", "const int LEFT_ALT", "const int LEFT_SUPER", "const int RIGHT_SHIFT", "const int RIGHT_CONTROL", "const int RIGHT_ALT", "const int RIGHT_SUPER", "const int MENU"};
        const char* mousekeycodenames[8] = {"const int MOUSE_BUTTON_1", "const int MOUSE_BUTTON_2", "const int MOUSE_BUTTON_3", "const int MOUSE_BUTTON_4", "const int MOUSE_BUTTON_5", "const int MOUSE_BUTTON_6", "const int MOUSE_BUTTON_7", "const int MOUSE_BUTTON_8"};
        for(int i = 1; i < 121; ++i) {
            scriptEngine->RegisterGlobalProperty(keycodeNames[i], (void*)&keycodes[i]);
        }
        for(int i = 0; i < 8; ++i) {
            scriptEngine->RegisterGlobalProperty(mousekeycodenames[i], (void*)&mousekeycodes[i]);
        }
        scriptEngine->SetDefaultNamespace(dNamespace);
        scriptEngine->RegisterGlobalProperty("const int CURSOR_NORMAL", (void*)&cursortypes[0]);
        scriptEngine->RegisterGlobalProperty("const int CURSOR_HIDDEN", (void*)&cursortypes[1]);
        scriptEngine->RegisterGlobalProperty("const int CURSOR_DISABLED", (void*)&cursortypes[2]);
    }

    const int AngelscriptInterface::keycodes[121] = { KEY_UNKNOWN, KEY_SPACE, KEY_APOSTROPHE, KEY_COMMA, KEY_MINUS, KEY_PERIOD, KEY_SLASH, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_SEMICOLON, KEY_EQUAL, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z, KEY_LEFT_BRACKET, KEY_BACKSLASH, KEY_RIGHT_BRACKET, KEY_GRAVE_ACCENT, KEY_WORLD_1, KEY_WORLD_2, KEY_ESCAPE, KEY_ENTER, KEY_TAB, KEY_BACKSPACE, KEY_INSERT, KEY_DELETE, KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP, KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_HOME, KEY_END, KEY_CAPS_LOCK, KEY_SCROLL_LOCK, KEY_NUM_LOCK, KEY_PRINT_SCREEN, KEY_PAUSE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F20, KEY_F21, KEY_F22, KEY_F23, KEY_F24, KEY_F25, KEY_KP_0, KEY_KP_1, KEY_KP_2, KEY_KP_3, KEY_KP_4, KEY_KP_5, KEY_KP_6, KEY_KP_7, KEY_KP_8, KEY_KP_9, KEY_KP_DECIMAL, KEY_KP_DIVIDE, KEY_KP_MULTIPLY, KEY_KP_SUBTRACT, KEY_KP_ADD, KEY_KP_ENTER, KEY_KP_EQUAL, KEY_LEFT_SHIFT, KEY_LEFT_CONTROL, KEY_LEFT_ALT, KEY_LEFT_SUPER, KEY_RIGHT_SHIFT, KEY_RIGHT_CONTROL, KEY_RIGHT_ALT, KEY_RIGHT_SUPER, KEY_MENU};
    const int AngelscriptInterface::mousekeycodes[8] = { MOUSE_BUTTON_1, MOUSE_BUTTON_2, MOUSE_BUTTON_3, MOUSE_BUTTON_4, MOUSE_BUTTON_5, MOUSE_BUTTON_6, MOUSE_BUTTON_7, MOUSE_BUTTON_8};

    // The class that scripts inherit from in angelscript
    const char AngelscriptInterface::scriptObjectSectionCode[] = {
    "shared abstract class ScriptObject {\n"
    "   protected Transform@ getTransform() {\n"
    "       return m_transform;\n"
    "   }\n"
    "   private Transform@ m_transform;\n"
    "};\n"
    };

    const int AngelscriptInterface::cursortypes[3] = { CURSOR_NORMAL, CURSOR_HIDDEN, CURSOR_DISABLED };



}