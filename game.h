class game {
    public:
        game();
        void init();
        void setSize(int x, int y);
        void setCursor(int x, int y);
        int getSizeX();
        int getSizeY();
        int getCurX();
        int getCurY();
        bool running();
        int countmines(int x, int y);
        void show(int x, int y);
        void stop();
        void render();
        void update();
        void destroy();
    private:
        int cur_x, cur_y;
        int size_x, size_y;
        bool run;
        int** grid;
        int ch;
};
