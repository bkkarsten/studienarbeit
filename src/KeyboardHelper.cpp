#include "KeyboardHelper.hpp"

int KeyboardHelper::modifiers() { 
    return QGuiApplication::queryKeyboardModifiers(); 
}