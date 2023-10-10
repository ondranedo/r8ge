/**
 *  AUTHOR:         Ondrej Nedojedly (https://www.github.com/ondranedo)
 *  DATA:           2023-10-10
 *  DESCRIPTION:    The main header file for the r8ge engine.
 *  LICENSE:        "../../LICENSE"
 *  HISTORY:
 *      2023-10-10  -   Initial version
 *
 *
 */

#ifndef R8GE_R8GE_H
#define R8GE_R8GE_H

#pragma region platform
    #ifdef linux
        #define R8GE_LINUX
    #elif _WIN32
        #define R8GE_WINDOWS
    #else//!_WIN32
        #error "Unknown/Unsupported platform"
    #endif//!linux

    #if defined(R8GE_WINDOWS) && defined(R8GE_SHARED)
        #ifdef R8GE_CORE_BUILD
            #define R8GE_API __declspec((__dllexport))
        #else
            #define R8GE_API __declspec((__dllimport))
        #endif//!R8GE_CORE_BUILD
    #else
        #define R8GE_API
    #endif//!R8GE_WINDOWS
#pragma endregion

#include <cassert>
#include <string>
#include <variant>
#include <queue>
#include <functional>
#include <memory>

namespace r8ge {
    namespace utility {
        /*
         * StringFormat is a utility class which provides the ability tu use
         * very basic `fmt-like` string formats.
         *
         * example:
         *  StringFormat("{1}, {0}!", {"World", "Hello"}) -> "Hello, World!"
         *  StringFormat("{}, {}! {}", {"World", "Hello"}) -> "World, Hello! "Hello"
         *  StringFormat("{} {} {}", {1, 2, 3}) -> "1 2 3"
         *  StringFormat("{0} {} {} {1}", {"Ahoj", 1, 2}) -> "Ahoj Ahoj 1 1"
         *  StringFormat("{}{}{}", {'a'}) -> "aaa"
         *  StringFormat("{0};{1};{2}", {10, 20}) -> "10;20;{missing_value}"
         *  StringFormat("{}, {}, {}, {}", {1,2}) -> "1, 2, 2, 2"
         *  StringFormat("\\{{}, \\{{}-{}-{}, \\{{2}{1}\\{{2}+{}}}}}", {0,1,2,3,4}) -> "{0, {1-2-3, {21{2+4}}}}"
         */
        R8GE_API class StringFormat {
        public:
            // Data types that can be formatted into string
            using ValidType = std::variant<
                    int, float, std::string, char, unsigned long, std::vector<std::string>
            >;
            using ValidList = std::initializer_list<ValidType>;
            StringFormat(const std::string& form, const ValidList& list);
            StringFormat(const std::string& str);
            StringFormat();

            [[nodiscard]] std::string to_string();

        private:
            std::string m_str;
        };

        // TimeStamp class, used for measuring time, and converting time to string.
        // May be used for measuring time between two points.
        R8GE_API class TimeStamp {
        public:
            enum _point {
                YEAR, MONTH, DAY, HOUR, MINUTE, SECOND, MILLISECOND, MICROSECOND, NANOSECONDS
                //%Y   %M     %D   %h    %m      %s       %q           %u
            };
            TimeStamp();

            // Converts localtime (time since epoch ISO 8601) to `TimeStamp::_point`,
            // if we use this for differing between times, an error is thrown.
            //    TimeStamp t1; // Time is: 2023-10-06 15:15:16 ....
            //    // ...
            //
            //    t1.sinceEpoch(TimeStamp::SECOND); -> 16
            //    t1.sinceEpoch(TimeStamp::HOUR); -> 15
            //    t1.sinceEpoch(TimeStamp::YEAR); -> 2023
            //    t1.sinceEpoch(TimeStamp::DAY); -> 6
            [[nodiscard]] std::size_t sinceEpoch(TimeStamp::_point timePoint) const;

            // Counts how many `TimeStamp::_point` have passed since POSIX time
            // ,not counting leap seconds (in ISO 8601: 1970-01-01T00:00:00Z).
            // If we use `TimeStamp` in calculation f.e:
            //    TimeStamp t1;
            //    // ...
            //    TimeStamp t2;
            //    (t2-t1).count(TimeStamp::SECOND);
            // It outputs how many seconds have passed since `t1` creation to `t2` creation
            [[nodiscard]] std::size_t count(TimeStamp::_point timePoint) const;

            // Uses https://strftime.org/ format, with addition to custom time formats for formating
            // milliseconds - %^{ms}
            // microseconds - %^{us}
            // nanoseconds  - %^{ns}
            [[nodiscard]] std::string to_string(const std::string& format = "%Y:%m:%d %H:%M:%S") const;

            TimeStamp& operator-(const TimeStamp&);

        private:
            std::size_t m_nanoseconds; // Since epoch
            bool m_subtracted;
        };


    }//!utility

    // Assert function used to log useful information about an error
    R8GE_API void assertImpl(const char * expr, unsigned long line, const char * fun, const char *msg, const utility::StringFormat::ValidList& list);

    // Logger class, used to log information, writes to a stdout for now
    R8GE_API  class Logger {
    public:
        Logger();
        ~Logger();

        enum class Priority {
            TRACE, DEBUG, ERROR, WARNI, FATAL
        };

    private:
        struct Log {
            utility::TimeStamp times;
            std::string raw_data;
            Priority priority;

            Log(const std::string& raw, Priority p);
        };

    public:
        // Sends a log to the queue, to be processed later by the logger
        void log(Priority p, const std::string& str);

        // Empties the log queue, and writes all logs to the log file (stdout for now)
        void emptyLogQueue();

    private:
        std::queue<Log> m_queue;
    };

    // Global main logging object, used to log information about the engine, and the game
    R8GE_API extern Logger* mainLogger;

    // Main Logger function, takes StringFormat::ValidType as arguments (see utility/StringFormat.h),
    // and call to the mainLogger (which is a global object)
    R8GE_API void mainLog(Logger::Priority p, const std::string& parser,
                 const std::initializer_list<utility::StringFormat::ValidType>& t);

    // Enum input/output codes for the engine
    enum class IOCode {
        //Mouse
        MBUTTON_1 = 0,
        MBUTTON_2 = 1,
        MBUTTON_3 = 2,
        MBUTTON_4 = 3,
        MBUTTON_5 = 4,
        MBUTTON_6 = 5,
        MBUTTON_7 = 6,
        MBUTTON_8 = 7,
        MBUTTON_LEFT = 8,
        MBUTTON_RIGHT = 9,
        MBUTTON_MIDDLE = 10,
        //Key
        SPACE = 32,
        APOSTROPHE = 39,  /* ' */
        COMMA = 44,  /* , */
        MINUS = 45,  /* - */
        PERIOD = 46,  /* . */
        SLASH = 47,  /* / */
        N0 = 48,
        N1 = 49,
        N2 = 50,
        N3 = 51,
        N4 = 52,
        N5 = 53,
        N6 = 54,
        N7 = 55,
        N8 = 56,
        N9 = 57,
        SEMICOLON = 59,  /* ; */
        EQUAL = 61,  /* = */
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,
        LEFT_BRACKET = 91,  /* [ */
        BACKSLASH = 92,  /* \ */
        RIGHT_BRACKET = 93,  /* ] */
        GRAVE_ACCENT = 96,  /* ` */
        ESCAPE = 256,
        ENTER = 257,
        TAB = 258,
        BACKSPACE = 259,
        INSERT = 260,
        DELETE = 261,
        RIGHT = 262,
        LEFT = 263,
        DOWN = 264,
        UP = 265,
        PAGE_UP = 266,
        PAGE_DOWN = 267,
        HOME = 268,
        END = 269,
        CAPS_LOCK = 280,
        SCROLL_LOCK = 281,
        NUM_LOCK = 282,
        PRINT_SCREEN = 283,
        PAUSE = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,
        KP_0 = 320,
        KP_1 = 321,
        KP_2 = 322,
        KP_3 = 323,
        KP_4 = 324,
        KP_5 = 325,
        KP_6 = 326,
        KP_7 = 327,
        KP_8 = 328,
        KP_9 = 329,
        KP_DECIMAL = 330,
        KP_DIVIDE = 331,
        KP_MULTIPLY = 332,
        KP_SUBTRACT = 333,
        KP_ADD = 334,
        KP_ENTER = 335,
        KP_EQUAL = 336,
        LEFT_SHIFT = 340,
        LEFT_CONTROL = 341,
        LEFT_ALT = 342,
        LEFT_SUPER = 343,
        RIGHT_SHIFT = 344,
        RIGHT_CONTROL = 345,
        RIGHT_ALT = 346,
        RIGHT_SUPER = 347,
        MENU = 348
    };

    // One keystroke from user
    // f.e.: CTRL + SHIFT + A
    //       CTRL + E
    //       MOUSE_LEFT + SHIFT
    struct IOStroke {
        IOCode iocode: 13;
        bool shift : 1;
        bool alt : 1;
        bool ctrl : 1;
    };

    // Event is used to send information across the engine.
    // Mainly by the windows and instance classes.
    class Event {
    public:
        enum class EventType : unsigned char
        {
            NONE,

            // Generated by windows
            WINDOW_RESIZED, WINDOW_CLOSED, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVED,
            KEY_PRESSED, KEY_RELEASED,
            MOUSE_PRESSED, MOUSE_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED

            // Generated by the engine
        };

    public:
        Event();
        virtual ~Event();

        // Type of the event, used to identify the event
        [[nodiscard]] EventType getType() const;

        // Is the event handled? If so, it should be ignored by the dispatcher
        [[nodiscard]] bool isHandled() const;

        // Set the event as handled, so it will be ignored by the next call of the dispatcher
        void setToHandled();

        [[nodiscard]] std::string to_string() const;

    protected:
        struct {
            EventType type : 7;
            bool handled : 1;
        } m_header;
    };

    struct KeyPressed : public Event {
        IOStroke stroke;
        bool repeat;
        KeyPressed(IOStroke stroke, bool repeat);
        static EventType getEventType();
    };

    struct KeyReleased : public Event {
        IOStroke stroke;

        KeyReleased(IOStroke _key);
        static EventType getEventType();
    };

    struct MouseMoved : public Event
    {
        double x, y;

        MouseMoved(double _x, double _y);
        static EventType getEventType();
    };

    struct MouseScrolled : public Event
    {
        double x, y;

        MouseScrolled(double _x, double _y);
        static EventType getEventType();
    };

    struct MousePressed : public Event
    {
        IOStroke stroke;

        explicit MousePressed(IOStroke _stroke);
        static EventType getEventType();
    };

    struct MouseReleased : public Event
    {
        IOStroke stroke;

        explicit MouseReleased(IOStroke _stroke);
        static EventType getEventType();
    };

    struct WindowResized : public Event
    {
        unsigned int x, y;

        WindowResized(unsigned int _x, unsigned int _y);
        static EventType getEventType();
    };

    struct WindowClosed : public Event
    {
        WindowClosed();
        static EventType getEventType();
    };

    struct WindowFocus : public Event
    {
        WindowFocus();
        static EventType getEventType();
    };

    struct WindowLostFocus : public Event
    {
        WindowLostFocus();
        static EventType getEventType();
    };

    struct WindowMoved : public Event
    {
        double x, y;
        WindowMoved(double _x, double _y);
        static EventType getEventType();
    };

    // One layer of Game/Editor/Sound Editor, used to separate the logic and rendering
    // This class should be defined by the user and registered in the GameInstance
    R8GE_API class Layer {
    public:
        explicit Layer(const std::string& name);
        virtual ~Layer();

        // Used to update the layer, called every frame
        virtual void update() const = 0;

        // Used to handle the events, called for every event that is delegated to the layer
        // if event is not handled, it will be delegated to the next layer, until its destroyed
        virtual void event(const std::shared_ptr<Event>& event) const = 0;

        // Called by the render loop to render the layer
        virtual void render() const = 0;


        [[nodiscard]] std::string getName() const;
    private:
        std::string m_name;
    };

    // Handles the layers, and the events to the layers
    // Is in the Instance class.
    // Event workflow:
    //       EventReceiver
    //           |
    //           v
    //       LayerSwitcher
    //           |
    //           v
    //       Layer[n] -> Layer[n-1] -> ... -> Layer[0]
    //
    // Update and Render workflow:
    //       UpdateAll / RenderAll
    //                 |
    //                 v
    //       Layer[0] -> Layer[1] -> ... -> Layer[n]
    class LayerSwitcher final {
    public:
        LayerSwitcher();

        // Pushes the layer to the front - first layer to receive the event, and the last to render
        void pushFront(const std::shared_ptr<Layer>& l);

        // Pushes the layer to the back - last layer to receive the event, and the first to render
        void pushBack(const std::shared_ptr<Layer>& l);

        // Pushes the layer to the front - first layer to receive the event, and the last to render
        template <typename T>
        void add () {
            pushFront(std::make_shared<T>());
        }

        // Pop according to the name
        void pop(const std::string& name);

        // Pop according to the index
        inline void pop(size_t index);

        // Pop the first layer - first layer to receive the event, and the last to render
        inline void popFront();

        // Pop the last layer - last layer to receive the event, and the first to render
        inline void popBack();

        // Sends the event to the layers
        // The event is sent to the layers from the last to the first
        // layer[n] -> layer[n-1] -> ... -> layer[0]
        void sendEvent(const std::shared_ptr<Event>& e) const;

        // Updates all the layers, starting from the most bottom layer; layer[0] -> layer[n]
        void updateAll() const;

        // Renders all the layers, starting from the most bottom layer; layer[0] -> layer[n]
        void renderAll() const;

        // Returns the string representation of the LayerSwitcher
        [[nodiscard]] std::string to_string() const;
    private:
        std::vector<std::shared_ptr<Layer>> m_layers;
    };

    // The main game instance, handles the layers, and the logic,
    // does not handle the main loop, or the event queue, or the window
    // This class should be registered to the Ar8ge class
    class Instance {
    public:
        Instance();
        virtual ~Instance();

        // Called when an event is sent to the instance, this function
        // should handle the event to layer switcher
        void eventReceiver(const std::shared_ptr<Event>& event);
        std::function<void(const std::shared_ptr<Event>&)> getEventReceiver();

        // Called when an event is sent to the instance, this function
        // should handle the event directly - it's not sent to the layer switcher
        virtual void directEvent(const std::shared_ptr<Event>& event) = 0;

        // Called every frame, this function should handle the update to layer switcher
        // and the logic, and the rendering
        void update();

        // Returns the reference to the layer switcher, used to add/remove layers
        [[nodiscard]] LayerSwitcher& layerSwitcher();
    private:
        LayerSwitcher m_layerSwitecher;
    };

    // The main game instance, handles the layers, and the logic,
    class GameInstance : public Instance {
    public:
        explicit GameInstance(const std::string& name);
        virtual ~GameInstance() override = default;

        // Called when class is initialized, not created!
        virtual void onInit() = 0;

        // Called evert frame, main core game logic should be here, not the rendering!
        // Rendering should be handled by the layers
        virtual void onUpdate() = 0;

        // Called when the class is destroyed, not deleted!
        virtual void onExit() = 0;

        [[nodiscard]] std::string getGameName() const;

    private:
        std::string m_name;
    };

    extern std::shared_ptr<r8ge::GameInstance> createGame();
}//!r8ge

#define R8GE_ADD_GAMEINSTANCE(x) namespace r8ge {std::shared_ptr<r8ge::GameInstance> createGame() {return std::make_shared<x>();}}

#define R8GE_ASSERT(expr, msg, ...) if(!(expr)) r8ge::assertImpl(#expr, __LINE__, __PRETTY_FUNCTION__, msg, {__VA_ARGS__})

#define R8GE_LOG_TRACE(str, ...) r8ge::mainLog(r8ge::Logger::Priority::TRACE, str,{__VA_ARGS__})
#define R8GE_LOG_DEBUG(str, ...) r8ge::mainLog(r8ge::Logger::Priority::DEBUG, str,{__VA_ARGS__})
#define R8GE_LOG_WARNI(str, ...) r8ge::mainLog(r8ge::Logger::Priority::WARNI, str,{__VA_ARGS__})
#define R8GE_LOG_ERROR(str, ...) r8ge::mainLog(r8ge::Logger::Priority::ERROR, str,{__VA_ARGS__})
#define R8GE_LOG_FATAL(str, ...) r8ge::mainLog(r8ge::Logger::Priority::FATAL, str,{__VA_ARGS__})

#define R8GE_LOG(...) R8GE_LOG_TRACE(__VA_ARGS__)

#endif//!R8GE_R8GE_H
