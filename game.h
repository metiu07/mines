class game {
    public:
        game();
        void init();
        void setSize(int x, int y);
        int getSizeX();
        int getSizeY();
        bool running();
        void render();
        void update();
        void destroy();
    private:
        int size_x, size_y;
        bool run;
};
