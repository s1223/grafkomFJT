
class Square : public Object {
private:
    int width;
    int height;
public:
    Square();
    Square(int x, int y, int w, int h);
    void render();
}