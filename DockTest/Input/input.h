#ifndef INPUT_H
#define INPUT_H
class QKeyEvent;
class QMouseEvent;
enum class InputState
{
    IDLE,
    DOWN,
    PRESSED,
    UP
};

class Input
{
public:
    Input();
    void KeyUpEvent(QKeyEvent *event);
    void KeyDownEvent(QKeyEvent *event);

    void MouseButtonUpEvent(QMouseEvent *event);
    void MouseButtonDownEvent(QMouseEvent *event);

    bool GetKeyPressed(int key);
    bool GetKeyUp(int key);
    bool GetKeyDown(int key);

    bool GetMouseButtonPressed(int key);
    bool GetMouseButtonUp(int key);
    bool GetMouseButtonDown(int key);

    void PostUpdate();

    enum{
        MAX_KEYS = 300,
        MAX_BUTTON = 10
    };
private:
    InputState keys[MAX_KEYS];
    InputState mouseButtons[MAX_BUTTON];

    int mouseX = 0;
    int mouseY = 0;
    int mouseXPrev = 0;
    int mouseYPrev = 0;

};

#endif // INPUT_H
