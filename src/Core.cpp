#include <Core.hpp>

//______________________CONSTRUCTORS AND DECONSTRUCTORS START_______________________________
Core::Core() {
    std::cout << "Constructing Core\n";
    this->_game = new Game;
    Settings settings = this->_game->getSettings();
    this->_width = settings.getResolutionX();
    this->_height = settings.getResolutionY();
    glfwInit();
    std::cout << "Core Constructed\n";
}

Core::Core(Core const & src) {
    std::cout << "Core Copy-Constructed\n";
    *this = src;
}

Core &              Core::operator=(Core const & src) {
    this->_win = src.getWin();
    this->_screen = src.getScreen();
    this->_game = src.getGame();
    this->_width = src.getWidth();
    this->_height = src.getHeight();
    return (*this);
}

Core::~Core() {
    std::cout << "De-Constructing Core\n";
    delete this->_game;
    this->_game = nullptr;
    std::cout << "closing nanogui screen" << std::endl;
    nanogui::shutdown();
    std::cout << "nanogui screen closed successfully" << std::endl;
    std::cout << "Core De-Constructed\n";
}

//___________________________________END________________________________________________

void    Core::updateKeys() {
    int     state;
    bool    pressed = false;

    state = glfwGetKey(_win, GLFW_KEY_LEFT);
    if (state == GLFW_PRESS) {
        _keyPressed = keys::LEFT;
        pressed = true;
    }
    state = glfwGetKey(_win, GLFW_KEY_RIGHT);
    if (state == GLFW_PRESS && !pressed) {
        _keyPressed = keys::RIGHT;
        pressed = true;
    }
    state = glfwGetKey(_win, GLFW_KEY_UP);
    if (state == GLFW_PRESS && !pressed) {
        _keyPressed = keys::UP;
        pressed = true;
    }
    state = glfwGetKey(_win, GLFW_KEY_DOWN);
    if (state == GLFW_PRESS && !pressed) {
        _keyPressed = keys::DOWN;
        pressed = true;
    }
    state = glfwGetKey(_win, GLFW_KEY_SPACE);
    if (state == GLFW_PRESS && !pressed) {
        _keyPressed = keys::SPACE;
        pressed = true;
    }
    state = glfwGetKey(_win, GLFW_KEY_ENTER);
    if (state == GLFW_PRESS && !pressed) {
        _keyPressed = keys::ENTER;
        pressed = true;
    }
    state = glfwGetKey(_win, GLFW_KEY_ESCAPE);
    if (state == GLFW_PRESS && !pressed) {
        _keyPressed = keys::ESC;
        pressed = true;
    }
    if (!pressed)
        _keyPressed = keys::NONE;
}

void	Core::run() {
    std::cout << "initializing" << std::endl;
    init();
    //gameLoop();
}

void                Core::init() {
    _win = nullptr;
    std::cout << "creating glfw window" << std::endl;
    glfwInit();

    glfwSetTime(0);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    _win = glfwCreateWindow(_width, _height, "Bomberman", nullptr, nullptr);
    if (_win == nullptr)
        fatalError("GLFW context is shot");
    glfwMakeContextCurrent(_win);
    glfwSwapInterval(1);
    std::cout << "glfw window created" << std::endl;
    mainMenu();
}

void    Core::mainMenu() {

    #if defined(NANOGUI_GLAD)
        std::cout << "initializing GLAD loader" << std::endl;
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            throw std::runtime_error("Could not initialize GLAD!");
        glGetError(); // pull and ignore unhandled errors like GL_INVALID_ENUM
    #endif
    std::cout << "creating nanogui screen" << std::endl;
    _screen = new nanogui::Screen;
    std::cout << "nanogui screen created" << std::endl;
    std::cout << "initializing nanogui window" << std::endl;
    _screen->initialize(_win, true);
    std::cout << "nanogui window initialized, screen integrated with window" << std::endl;

    bool enabled = true;
    nanogui::FormHelper *gui = new nanogui::FormHelper(_screen);
    nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Fuckyeah BITCH!");

    gui->addButton("A button", []() { std::cout << "Button pressed." << std::endl; });
    std::cout << "visualizing screen" << std::endl;
    _screen->setVisible(true);
    _screen->performLayout();
    nanoguiWindow->center();

    std::cout << "starting screen loop" << std::endl;
    while (!glfwWindowShouldClose(_win)) {
        glfwPollEvents();
        updateKeys();
        if (_keyPressed != keys::NONE)
            std::cout << "KEY PRESSED" << std::endl;
        glfwGetFramebufferSize(_win, &_width, &_height);
        glViewport(0, 0, _width, _height);
        glClear(GL_COLOR_BUFFER_BIT);

        _screen->drawContents();
        _screen->drawWidgets();
        glfwSwapBuffers(_win);
    }
    glfwTerminate();

}

//Core::keys    Core::getAsciiKey(){
//    if (keyPressArr[SDL_SCANCODE_LEFT])
//        return _key::LEFT;
//    else if (keyPressArr[SDL_SCANCODE_RIGHT])
//        return _key::RIGHT;
//    else if (keyPressArr[SDL_SCANCODE_UP])
//        return _key::UP;
//    else if (keyPressArr[SDL_SCANCODE_DOWN])
//        return _key::DOWN;
//    else if (keyPressArr[SDL_SCANCODE_SPACE])
//        return _key::SPACE;
//    else if (keyPressArr[SDL_SCANCODE_RETURN])
//        return _key::ENTER;
//    else if (keyPressArr[SDL_SCANCODE_ESCAPE])
//        return _key::ESC;
//    else
//        return _key::NONE;
//}

void                Core::input() {


    int state = glfwGetKey(_win, GLFW_KEY_ESCAPE);
    if (state == GLFW_PRESS)
        this->_game->setState(GameState::EXIT);
}

void                Core::gameLoop() {
    while (this->_game->getState() != GameState::EXIT && !glfwWindowShouldClose(_win)) {
        input();
        drawGame();
    }
}

void                Core::drawGame() {
    glfwGetFramebufferSize(_win, &_width, &_height);

    glViewport(0, 0, _width, _height);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(_win);
    glfwPollEvents();
}

//__________________________GETTERS AND SETTERS________________________________________

Game		        *Core::getGame() const {
    return (this->_game);
}

void		        Core::setGame(Game *newGame) {
    this->_game = newGame;
}

GLFWwindow          *Core::getWin() const {
    return (this->_win);
}

void                Core::setWin(GLFWwindow *win) {
    this->_win = win;
}

nanogui::Screen     *Core::getScreen() const {
    return (this->_screen);
}

void                Core::setScreen(nanogui::Screen *screen){
    this->_screen = screen;
}

int			Core::getWidth() const {
    return (this->_width);
}

void		Core::setWidth(const int newWidth) {
    this->_width = newWidth;
}

int			Core::getHeight() const {
    return (this->_height);
}

void		Core::setHeight(const int newHeight) {
    this->_height = newHeight;
}

keys        Core::getKeyPressed() const {
    return (this->_keyPressed);
}

void        Core::setKeyPressed(const keys newkey) {
    this->_keyPressed  = newkey;
}

keys        Core::getPreKeyPressed() const {
    return (this->_keyPressed);
}

void        Core::setPreKeyPressed(const keys newkey) {
    this->_keyPressed  = newkey;
}

//__________________________________END______________________________________

void		Core::fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Press any key to exit" << std::endl;
    int temp;
    std::cin >> temp;
    exit(1);
}

//____________________________NON MEMBER FUNCTIONS________________________________

//__________________________________END______________________________________
