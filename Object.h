
class Object {
protected:    
    int x, y; //Center position of the object

public:
    Object();
    Object(int x, int y);
    virtual void render();
};