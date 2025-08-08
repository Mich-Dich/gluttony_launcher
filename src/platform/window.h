#pragma once

struct GLFWwindow;
struct VkExtent2D;
struct VkInstance_T;
struct VkSurfaceKHR_T;

class event;
class application;



namespace AT {

	using EventCallbackFn = std::function<void(event&)>;
	
	enum class window_size_state {
		windowed,
		minimised,
		fullscreen,
		fullscreen_windowed,
	};
	
	struct window_attrib {
	
		std::string title;
		u32 pos_x = 100;
		u32 pos_y = 100;
		f64 cursor_pos_x{};
		f64 cursor_pos_y{};
		u32 width{};
		u32 height{};
		bool vsync = false;
		application* app_ref{};
		window_size_state size_state = window_size_state::windowed;
	
		EventCallbackFn event_callback;
	
		window_attrib(const std::string title = "Application Template", const u32 width = 1600, const  u32 height = 900, const  bool vsync = false, const EventCallbackFn& callback = nullptr)
			: title(title), width(width), height(height), vsync(vsync), event_callback(callback){}
	};
	
	// ==============================================================  window ==============================================================
	
	class window {
	public:
	
		using EventCallbackFn = std::function<void(event&)>;
	
		window(window_attrib attributes = window_attrib());
		~window();
	
		DELETE_COPY_CONSTRUCTOR(window);
	
		GETTER_SETTER_C(bool, 													vsync, m_data.vsync)
		GETTER_C(u32, 															width, m_data.width)
		GETTER_C(u32, 															height, m_data.height)

		FORCEINLINE window_attrib get_attributes() const						{ return m_data; }
		FORCEINLINE GLFWwindow* get_window() const								{ return m_Window; }
		FORCEINLINE void set_event_callback(const EventCallbackFn& callback)	{ m_data.event_callback = callback; }
		FORCEINLINE f64 get_cursor_pos_x() const								{ return m_data.cursor_pos_x; }
		FORCEINLINE f64 get_cursor_pos_y() const								{ return m_data.cursor_pos_y; }
		FORCEINLINE window_size_state get_window_size_state() const				{ return m_data.size_state; }
		void get_framebuffer_size(int& width, int& height);
	
		void show_window(bool show);
		bool is_maximized();
		void minimize_window();
		void restore_window();
		void maximize_window();
		void show_titlebar(bool show);
		void get_monitor_size(int* width, int* height);
		void get_mouse_position(glm::vec2& pos);
	
	#if defined(RENDER_API_VULKAN)
		void create_vulkan_surface(VkInstance_T* instance, VkSurfaceKHR_T** get_surface);
	#endif
	
		glm::ivec2 get_extend();
		bool should_close();
		void poll_events();
		void capture_cursor();
		void release_cursor();
	
		template<typename Func>
		void queue_event(Func&& func) {
	
			m_event_queue.push(func);
		}
	
	private:
	
		std::mutex m_event_queue_mutex;
		std::queue<std::function<void()>> m_event_queue;
		std::filesystem::path m_icon_path;
	
		void bind_event_calbacks();
	
		window_attrib m_data{};
		GLFWwindow* m_Window{};
	};

}	
