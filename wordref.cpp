#include "wordref.h"

WordRef::WordRef() : active(false)
{
}

void WordRef::setWordRef(int pos, bool isOnTop) {
    this->pos = pos;
    this->onTop = isOnTop;
    this->active = true;
}

void WordRef::deactivate() {
    active = false;
}

int WordRef::getPos() {
    return pos;
}

bool WordRef::isOnTop() {
    return onTop;
}

bool WordRef::isActive() {
    return active;
}
