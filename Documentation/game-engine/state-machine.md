# State Machine

In order to manage all different screens, like the different menus and the game screen, we decided to implement a state machine.&#x20;

The state machine is split up in different classes. The most important are the "StateMachine" and the "State" class. The "StateMachine"-Class contains the stack of states and the "State"-Class builds the base of all screens. &#x20;

<figure><img src="../assets/Screenshot from 2023-01-31 14-44-03.png" alt=""><figcaption></figcaption></figure>

To add a new screen you simply have to create a new class like the "ScreenStates"-Class in the following picture. The "update"-function contains event management, the "draw"-function contains everything relevant to display the scene. The new scene should be put inside the "Client"-folder.

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
15        CustomState(StateMachine &t_machine, sf::RenderWindow &t_window,
16                               MusicPlayer &t_music_player, std::size_t T_flag,
17                               bool t_replace = true);
18        void pause() override;
19        void resume() override;
20        void update() override;
21        void draw() override;
22
23    private:
24        sf::Texture m_bg_t;
25        sf::Sprite m_bg_s;
26        std::size_t m_flag;
27 };
28
29 #endif /* !CUSTOMSTATE_HPP_ */
```

CustomState.cpp:

```
1  #include "{PATH_TO_FILE}/CustomState.hpp"
2  #include "{PATH_TO_FILE}/MainState.hpp" 
3  #include "{PATH_TO_FILE}/SettingsState.hpp"
4  // or add other states
5
6  CustomState::CustomState(StateMachine &t_machine, sf::RenderWindow &t_window,
7                          MusicPlayer &t_music_player, std::size_t T_flag,
8                          bool t_replace = true)
9        : State(t_machine, t_window, t_music_player, t_replace), 
10         m_flag(t_flag) {
11     if (!m_bg_t.loadFromFile("{PATH_TO_FILE}/{IMAGE_NAME}.{png/jpg}")) {
12         throw std::runtime_error("Unable to load image.");
13     };
14     float size_x = m_window.getSize().x;
15     float size_y = m_window.getSize().y;
16     float scale_x = size_x / m_bg_t.getSize().x;
17     float scale_y = size_y / m_bg_t.getSize().y;
18     m_bg_s.setTexture(m_bg_t, true);
19     m_bg_s.setScale(scale_x, scale_y);
20     m_music_player.play(MusicID::{MUSIC_NAME});
21 }
22
23 void CustomState::pause() { std::cout << "CustomState Pause\n"; }
24
25 void CustomState::resume() { std::cout << "CustomState resume\n"; }
26
27 void MainState::update() {
28     for (sf::Event = sf::Event{}; m_window.pollEvent(event);) {
29         sf::Vector2i mouse_pos = sf::Mouse::getPosition(m_window);
30         sf::Vector2f mouse_pos_f(static_cast(mouse_pos.x),
31                                  static_cast(mouse_pos.y));
32         switch (event.type) {
33             case sf::Event::Closed:
34                 m_state_machine.quit();
35                 break;
36             case sf::Event::KeyPressed:
37                 switch (event.key.code) {
38                     case sf::Keyboard::Escape:
39                         m_state_machine.quit();
40                         break;
41                     default:
42                         break;
43                 }
44                 break;
45             default:
46                 break;
47        }
48     }
49 } 
50 void CustomState::draw() {
51     m_window.clear();
52     m_window.draw(m_bg_s);
53     m_window.display();
54 }
```



[Back](../../README.md)
