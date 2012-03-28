#ifndef WORDREF_H
#define WORDREF_H

class WordRef
{
private:
    bool active;
    int pos;
    bool onTop;
public:
    WordRef();
    void setWordRef(int pos, bool isOnTop);
    void deactivate();
    int getPos();
    bool isOnTop();
    bool isActive();
};

#endif // WORDREF_H
