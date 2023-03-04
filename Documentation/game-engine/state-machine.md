# State Machine

In order to manage all different screens, like the different menus and the game screen, we decided to implement a state machine.&#x20;

The state machine is split up in different classes. The most important are the "StateMachine" and the "State" class. The "StateMachine"-Class contains the stack of states and the "State"-Class builds the base of all screens. &#x20;

<figure><img src="../assets/Screenshot from 2023-01-31 14-44-03.png" alt=""><figcaption></figcaption></figure>

To add a new screen you simply have to create a new class like the "ScreenStates"-Class in the following picture. The "update"-function contains event management, the "draw"-function contains everything relevant to display the scene. The new scene should be put inside the "States"-folder, which you find under "GameEngine" -> "src".

Example:

CustomState.hpp:

```
1  #ifndef CUSTOMSTATE_HPP_
2  #define CUSTOMSTATE_HPP_
3 
4  #include <SFML/Graphics/RenderWindow.hpp>
5  #include <SFML/Graphics/Sprite.hpp>
6  #include <SFML/Graphics/Texture.hpp>
7  #include <SFML/Window/Event.hpp>
8  
9  #include "{PATH_TO_FILE}/MusicPlayer.hpp"
10 #include "{PATH_TO_FILE}/State.hpp"
11 #incldue "{PATH_TO_FILE}/StateMachine.hpp"
12 
13 class CustomState final : public State {
14    public:
15        CustomState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
16                               MusicPlayer &t_music_player, std::size_t T_flag,
17                               bool t_replace = true);
18        void pause() override;
19        void resume() override;
20        void update() override;
21        void draw() override;
22
23    private:
24        rtype::ITexture *m_bg_t;
25        rtype::ISprite *m_bg_s;
26        std::size_t m_flag;
27 };
28
29 #endif /* !CUSTOMSTATE_HPP_ */
30
```

CustomState.cpp:

```
1  #include "{PATH_TO_FILE}/CustomState.hpp"
2  #include "{PATH_TO_FILE}/MainState.hpp" 
3  #include "{PATH_TO_FILE}/SettingsState.hpp"
4  // or add other states
5
6  CustomState::CustomState(StateMachine &t_machine, rtype::IRenderWindow *t_window,
7                          MusicPlayer &t_music_player, std::size_t T_flag,
8                          bool t_replace = true)
9        : State(t_machine, t_window, t_music_player, t_replace), 
10         m_flag(t_flag) {
11     m_bg_t = new rtype::Texture();
12     m_bg_s = new rtype::Sprite();
13     if (!m_bg_t->loadFromFile("{PATH_TO_FILE}/{IMAGE_NAME}.{png/jpg}")) {
14         throw std::runtime_error("Unable to load image.");
15     };
16     float size_x = m_window->getSize().x;
17     float size_y = m_window->getSize().y;
18     float scale_x = size_x / m_bg_t->getSize().x;
19     float scale_y = size_y / m_bg_t->getSize().y;
20     m_bg_s->setTexture(m_bg_t, true);
21     m_bg_s->setScale({scale_x, scale_y});
22     m_music_player.play(MusicID::{MUSIC_NAME});
23 }
24
25 void CustomState::pause() { std::cout << "CustomState Pause\n"; }
26
27 void CustomState::resume() { std::cout << "CustomState resume\n"; }
28
29 void MainState::update() {
30     for (auto event = rtype::Event{}; m_window->pollEvent(event);) {
31         sf::Vector2i mouse_pos = m_mouse->getMousePosition(m_window);
32         sf::Vector2f mouse_pos_f(static_cast(mouse_pos.x),
33                                  static_cast(mouse_pos.y));
34         switch (event.type) {
35             case rtype::EventType::Closed:
36                 m_state_machine.quit();
37                 break;
38             case rtype::EventType::KeyPressed:
39                 switch (event.key.code) {
40                     case rtype::EventKey::Escape:
41                         m_state_machine.quit();
42                         break;
43                     default:
44                         break;
45                 }
46                 break;
47             default:
48                 break;
49        }
50     }
51 } 
52
53 void CustomState::draw() {
54     m_window->clear();
55     m_window->draw(m_bg_s);
56     m_window->display();
57 }
58
```



[Back](../overview/game-engine.md)
