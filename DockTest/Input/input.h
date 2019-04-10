#ifndef INPUT_H
#define INPUT_H
class QKeyEvent;
enum class InputState
{
    DOWN,
    PRESSED,
    UP
};

class Input
{
public:
    Input();
    void KeyPressedEvent(QKeyEvent *event);
    void KeyUpEvent(QKeyEvent *event);
    void KeyDownEvent(QKeyEvent *event);

    void MouseButtonPressedEvent(QKeyEvent *event);
    void MouseButtonUpEvent(QKeyEvent *event);
    void MouseButtonDownEvent(QKeyEvent *event);

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
