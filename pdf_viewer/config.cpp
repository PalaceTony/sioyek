#include "config.h"
#include "utils.h"
#include <cassert>
#include <map>
#include <qdir.h>
//#include <ui.h>

extern float ZOOM_INC_FACTOR;
extern float GAMMA;
extern float VERTICAL_MOVE_AMOUNT;
extern float HORIZONTAL_MOVE_AMOUNT;
extern float MOVE_SCREEN_PERCENTAGE;
extern float BACKGROUND_COLOR[3];
extern float UNSELECTED_SEARCH_HIGHLIGHT_COLOR[3];
extern float DARK_MODE_BACKGROUND_COLOR[3];
extern float CUSTOM_COLOR_MODE_EMPTY_BACKGROUND_COLOR[3];
extern float DARK_MODE_CONTRAST;
extern bool FLAT_TABLE_OF_CONTENTS;
extern bool SMALL_TOC;
extern bool SHOULD_USE_MULTIPLE_MONITORS;
extern bool SORT_BOOKMARKS_BY_LOCATION;
extern bool SHOULD_LOAD_TUTORIAL_WHEN_NO_OTHER_FILE;
extern bool SHOULD_LAUNCH_NEW_INSTANCE;
extern bool SHOULD_LAUNCH_NEW_WINDOW;
extern bool SHOULD_CHECK_FOR_LATEST_VERSION_ON_STARTUP;
extern bool SHOULD_DRAW_UNRENDERED_PAGES;
extern bool HOVER_OVERVIEW;
//extern bool AUTO_EMBED_ANNOTATIONS;
extern bool DEFAULT_DARK_MODE;
extern float HIGHLIGHT_COLORS[26 * 3];
extern std::wstring SEARCH_URLS[26];
extern std::wstring EXECUTE_COMMANDS[26];
extern std::wstring LIBGEN_ADDRESS;
extern std::wstring GOOGLE_SCHOLAR_ADDRESS;
extern std::wstring INVERSE_SEARCH_COMMAND;
extern std::wstring SHARED_DATABASE_PATH;
extern std::wstring ITEM_LIST_PREFIX;
extern float VISUAL_MARK_NEXT_PAGE_FRACTION;
extern float VISUAL_MARK_NEXT_PAGE_THRESHOLD;
extern std::wstring UI_FONT_FACE_NAME;
extern std::wstring MIDDLE_CLICK_SEARCH_ENGINE;
extern std::wstring SHIFT_MIDDLE_CLICK_SEARCH_ENGINE;
extern std::wstring STARTUP_COMMANDS;
extern std::wstring SHUTDOWN_COMMANDS;
extern int FONT_SIZE;
extern float CUSTOM_BACKGROUND_COLOR[3];
extern float CUSTOM_TEXT_COLOR[3];
extern bool RERENDER_OVERVIEW;
extern bool WHEEL_ZOOM_ON_CURSOR;
extern bool RULER_MODE;
extern bool LINEAR_TEXTURE_FILTERING;
extern float DISPLAY_RESOLUTION_SCALE;
extern float STATUS_BAR_COLOR[3];
extern float STATUS_BAR_TEXT_COLOR[3];
extern float UI_SELECTED_TEXT_COLOR[3];
extern float UI_SELECTED_BACKGROUND_COLOR[3];
extern int STATUS_BAR_FONT_SIZE;
extern int MAIN_WINDOW_SIZE[2];
extern int HELPER_WINDOW_SIZE[2];
extern int MAIN_WINDOW_MOVE[2];
extern int HELPER_WINDOW_MOVE[2];
extern float TOUCHPAD_SENSITIVITY;
extern float SCROLL_VIEW_SENSITIVITY;
extern float PAGE_SEPARATOR_WIDTH;
extern float PAGE_SEPARATOR_COLOR[3];
extern int SINGLE_MAIN_WINDOW_SIZE[2];
extern int SINGLE_MAIN_WINDOW_MOVE[2];
extern float FIT_TO_PAGE_WIDTH_RATIO;
extern float RULER_PADDING;
extern float RULER_X_PADDING;
extern std::wstring TEXT_HIGHLIGHT_URL;
extern bool TEXT_SUMMARY_HIGHLIGHT_SHOULD_REFINE;
extern bool TEXT_SUMMARY_HIGHLIGHT_SHOULD_FILL;
extern int TEXT_SUMMARY_CONTEXT_SIZE;
extern bool USE_HEURISTIC_IF_TEXT_SUMMARY_NOT_AVAILABLE;
extern std::wstring PAPERS_FOLDER_PATH;
extern bool ENABLE_EXPERIMENTAL_FEATURES;
extern bool CREATE_TABLE_OF_CONTENTS_IF_NOT_EXISTS;
extern int MAX_CREATED_TABLE_OF_CONTENTS_SIZE;
extern bool FORCE_CUSTOM_LINE_ALGORITHM;
extern float OVERVIEW_SIZE[2];
extern float OVERVIEW_OFFSET[2];
extern bool IGNORE_WHITESPACE_IN_PRESENTATION_MODE;
extern bool EXACT_HIGHLIGHT_SELECT;
extern bool SHOW_DOC_PATH;
extern float FASTREAD_OPACITY;
extern bool SHOULD_WARN_ABOUT_USER_KEY_OVERRIDE;
extern bool SINGLE_CLICK_SELECTS_WORDS;
extern std::wstring SHIFT_CLICK_COMMAND;
extern std::wstring CONTROL_CLICK_COMMAND;
extern std::wstring SHIFT_RIGHT_CLICK_COMMAND;
extern std::wstring CONTROL_RIGHT_CLICK_COMMAND;
extern std::wstring ALT_CLICK_COMMAND;
extern std::wstring ALT_RIGHT_CLICK_COMMAND;
extern bool USE_LEGACY_KEYBINDS;
extern bool MULTILINE_MENUS;
extern bool START_WITH_HELPER_WINDOW;
extern std::map<std::wstring, std::wstring> ADDITIONAL_COMMANDS;
extern std::map<std::wstring, std::wstring> ADDITIONAL_MACROS;
extern bool PRERENDER_NEXT_PAGE;
extern bool EMACS_MODE;
extern bool HIGHLIGHT_MIDDLE_CLICK;
extern float HYPERDRIVE_SPEED_FACTOR;
extern float SMOOTH_SCROLL_SPEED;
extern float SMOOTH_SCROLL_DRAG;
extern bool IGNORE_STATUSBAR_IN_PRESENTATION_MODE;
extern bool SUPER_FAST_SEARCH;
extern bool SHOW_CLOSEST_BOOKMARK_IN_STATUSBAR;
extern int PRERENDERED_PAGE_COUNT;
extern bool CASE_SENSITIVE_SEARCH;
extern bool SHOW_DOCUMENT_NAME_IN_STATUSBAR;
extern bool SHOW_CLOSE_PORTAL_IN_STATUSBAR;
extern bool NUMERIC_TAGS;
extern bool SHOULD_HIGHLIGHT_LINKS;
extern bool SHOULD_HIGHLIGHT_UNSELECTED_SEARCH;
extern int KEYBOARD_SELECT_FONT_SIZE;
extern bool FUZZY_SEARCHING;
extern float CUSTOM_COLOR_CONTRAST;
extern bool DEBUG;
extern float HIGHLIGHT_DELETE_THRESHOLD;
extern std::wstring DEFAULT_OPEN_FILE_PATH;
extern std::wstring STATUS_BAR_FORMAT;
extern bool INVERTED_HORIZONTAL_SCROLLING;
extern bool TOC_JUMP_ALIGN_TOP;
extern float KEYBOARD_SELECT_BACKGROUND_COLOR[4];
extern float KEYBOARD_SELECT_TEXT_COLOR[4];
extern bool AUTOCENTER_VISUAL_SCROLL;
extern bool ALPHABETIC_LINK_TAGS;
extern bool VIMTEX_WSL_FIX;
#ifdef SIOYEK_ANDROID
extern Path android_config_path;
#endif

template<typename T>
void* generic_deserializer(std::wstringstream& stream, void* res_) {
	T* res = static_cast<T*>(res_);
	stream >> *res;
	return res;
}

void int_serializer(void* int_pointer, std::wstringstream& stream) {
	stream << *(int*)int_pointer;
}

void bool_serializer(void* bool_pointer, std::wstringstream& stream) {
	stream << *(bool*)bool_pointer;
}

void string_serializer(void* string_pointer, std::wstringstream& stream) {
	stream << *(std::wstring*)string_pointer;
}

void* string_deserializer(std::wstringstream& stream, void* res_) {
	assert(res_ != nullptr);
	//delete res_;

	std::wstring* res = static_cast<std::wstring*>(res_);
	res->clear();
	std::getline(stream, *res);
	while (iswspace((*res)[0])) {
		res->erase(res->begin());

	}
	return res;
}



template<int N, typename T>
void vec_n_serializer(void* vec_n_pointer, std::wstringstream& stream) {
	for (int i = 0; i < N; i++) {
		stream << *(((T*)vec_n_pointer) + i);
		if (i < N - 1) {
			stream << L" ";
		}
	}
}

//template<int N>
//void vec_n_serializer<N, float>(void* vec_n_pointer, std::wstringstream& stream) {
//	for (int i = 0; i < N; i++) {
//		stream << *(((T*)vec_n_pointer) + i);
//	}
//}

template<int N, typename T>
void* vec_n_deserializer(std::wstringstream& stream, void* res_) {
	assert(res_ != nullptr);
	T* res = (T*)res_;
	if (res == nullptr) {
		res = new T[N];
	}
	for (int i = 0; i < N; i++) {
		stream >> *(res + i);
	}

	return res;
}

template <int N>
void* colorn_deserializer(std::wstringstream& stream, void* res_) {

	assert(res_ != nullptr);
	float* res = (float*)res_;
	if (res == nullptr) {
		res = new float[N];
	}
	while (std::isspace(stream.peek())) {
		stream.ignore();
	}
	if (stream.peek() == '#') {
		std::wstring rest;
		std::getline(stream, rest);
		hexademical_to_normalized_color(rest, res, N);
	}
	else {
		for (int i = 0; i < N; i++) {
			stream >> *(res + i);
		}
	}

	return res;
}

void float_serializer(void* float_pointer, std::wstringstream& stream) {
	stream << *(float*)float_pointer;
}


void* Config::get_value() {
	return value;
}

Config* ConfigManager::get_mut_config_with_name(std::wstring config_name) {
	for (auto& it : configs) {
		if (it.name == config_name) return &it;
	}
	return nullptr;
}

bool ensure_between_0_and_1(const QStringList& parts) {
	bool ok = false;
	for (int i = 0; i < parts.size(); i++) {
		int val = parts.at(i).toFloat(&ok);
		if (!ok) {
			std::wcout << L"Error: invalid value for color component: " << parts.at(i).toStdWString() << "\n";
			return false;
		}
		if (val < 0 || val > 1) {
			std::wcout << L"Error: invalid value for color component (must be between 0 and 1): " << parts.at(i).toStdWString() << "\n";
			return false;
		}
	}
	return true;
}

template <int N>
bool colorn_validator(const std::wstring& str) {
	QString qstr = QString::fromStdWString(str);
	auto parts = qstr.trimmed().split(' ', Qt::SplitBehaviorFlags::SkipEmptyParts);
	if (parts.size() != N) {
		if (parts.size() == 1) {
			if (parts.at(0).at(0) == '#') {
				if (parts.at(0).size() == (1 + 2 * N)) {
					return true;
				}
			}

		}
		std::wcout << L"Error: required 3 values for color, but got " << parts.size() << "\n";
		return false;
	}
	if (!ensure_between_0_and_1(parts)) {
		return false;
	}
	return true;
}
//bool color_3_validator(const std::wstring& str) {
//	QString qstr = QString::fromStdWString(str);
//	auto parts = qstr.trimmed().split(' ', Qt::SplitBehaviorFlags::SkipEmptyParts);
//	if (parts.size() != 3) {
//		std::wcout << L"Error: required 3 values for color, but got " << parts.size() << "\n";
//		return false;
//	}
//	if (!ensure_between_0_and_1(parts)) {
//		return false;
//	}
//	return true;
//}
//
//bool color_4_validator(const std::wstring& str) {
//	QString qstr = QString::fromStdWString(str);
//	auto parts = qstr.trimmed().split(' ', Qt::SplitBehaviorFlags::SkipEmptyParts);
//	if (parts.size() != 4) {
//		std::wcout << L"Error: required 4 values for color, but got " << parts.size() << "\n";
//		return false;
//	}
//	if (!ensure_between_0_and_1(parts)) {
//		return false;
//	}
//	return true;
//}

bool bool_validator(const std::wstring& str) {
	QString qstr = QString::fromStdWString(str);
	auto parts = qstr.trimmed().split(' ', Qt::SplitBehaviorFlags::SkipEmptyParts);
	std::wstring msg = L"Bool values should be either 0 or 1, but got ";
	if (parts.size() != 1) {
		std::wcout << msg << str << L"\n";
		return false;
	}
	if (parts.at(0).trimmed().toStdWString() == L"0" || parts.at(0).trimmed().toStdWString() == L"1") {
		return true;
	}
	std::wcout << msg << str << L"\n";
	return false;
}



ConfigManager::ConfigManager(const Path& default_path, const Path& auto_path ,const std::vector<Path>& user_paths) {

	user_config_paths = user_paths;
	auto ivec2_serializer = vec_n_serializer<2, int>;
	auto ivec2_deserializer = vec_n_deserializer<2, int>;
	auto fvec2_serializer = vec_n_serializer<2, float>;
	auto fvec2_deserializer = vec_n_deserializer<2, float>;
	auto vec3_serializer = vec_n_serializer<3, float>;
	auto vec4_serializer = vec_n_serializer<4, float>;
	auto vec3_deserializer = vec_n_deserializer<3, float>;
	auto vec4_deserializer = vec_n_deserializer<4, float>;
	auto float_deserializer = generic_deserializer<float>;
	auto int_deserializer = generic_deserializer<int>;
	auto bool_deserializer = generic_deserializer<bool>;
	auto color3_deserializer = colorn_deserializer<3>;
	auto color4_deserializer = colorn_deserializer<4>;
	auto color_3_validator = colorn_validator<3>;
	auto color_4_validator = colorn_validator<4>;

    configs.push_back({ L"text_highlight_color", ConfigType::Color3, DEFAULT_TEXT_HIGHLIGHT_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"vertical_line_color", ConfigType::Color4,DEFAULT_VERTICAL_LINE_COLOR, vec4_serializer, color4_deserializer, color_4_validator });
    configs.push_back({ L"visual_mark_color", ConfigType::Color4, DEFAULT_VERTICAL_LINE_COLOR, vec4_serializer, color4_deserializer, color_4_validator });
    configs.push_back({ L"search_highlight_color", ConfigType::Color3, DEFAULT_SEARCH_HIGHLIGHT_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"unselected_search_highlight_color", ConfigType::Color3, UNSELECTED_SEARCH_HIGHLIGHT_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"link_highlight_color", ConfigType::Color3 , DEFAULT_LINK_HIGHLIGHT_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"synctex_highlight_color", ConfigType::Color3, DEFAULT_SYNCTEX_HIGHLIGHT_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"background_color", ConfigType::Color3, BACKGROUND_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"dark_mode_background_color", ConfigType::Color3, DARK_MODE_BACKGROUND_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"custom_color_mode_empty_background_color", ConfigType::Color3, CUSTOM_COLOR_MODE_EMPTY_BACKGROUND_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"dark_mode_contrast", ConfigType::Float, &DARK_MODE_CONTRAST, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"custom_color_contrast", ConfigType::Float, &CUSTOM_COLOR_CONTRAST, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"default_dark_mode", ConfigType::Bool, &DEFAULT_DARK_MODE, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"google_scholar_address", ConfigType::String, &GOOGLE_SCHOLAR_ADDRESS, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"item_list_prefix", ConfigType::String, &ITEM_LIST_PREFIX, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"inverse_search_command", ConfigType::String, &INVERSE_SEARCH_COMMAND, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"libgen_address", ConfigType::String, &LIBGEN_ADDRESS, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"zoom_inc_factor", ConfigType::Float, &ZOOM_INC_FACTOR, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"vertical_move_amount", ConfigType::Float, &VERTICAL_MOVE_AMOUNT, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"horizontal_move_amount", ConfigType::Float, &HORIZONTAL_MOVE_AMOUNT, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"move_screen_percentage", ConfigType::Float, &MOVE_SCREEN_PERCENTAGE, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"move_screen_ratio", ConfigType::Float, &MOVE_SCREEN_PERCENTAGE, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"flat_toc", ConfigType::Bool, &FLAT_TABLE_OF_CONTENTS, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"should_use_multiple_monitors", ConfigType::Bool, &SHOULD_USE_MULTIPLE_MONITORS, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"should_load_tutorial_when_no_other_file", ConfigType::Bool, &SHOULD_LOAD_TUTORIAL_WHEN_NO_OTHER_FILE, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"should_launch_new_instance", ConfigType::Bool, &SHOULD_LAUNCH_NEW_INSTANCE, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"should_launch_new_window", ConfigType::Bool, &SHOULD_LAUNCH_NEW_WINDOW, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"should_draw_unrendered_pages", ConfigType::Bool, &SHOULD_DRAW_UNRENDERED_PAGES, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"check_for_updates_on_startup", ConfigType::Bool, &SHOULD_CHECK_FOR_LATEST_VERSION_ON_STARTUP, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"sort_bookmarks_by_location", ConfigType::Bool, &SORT_BOOKMARKS_BY_LOCATION, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"shared_database_path", ConfigType::String, &SHARED_DATABASE_PATH, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"hover_overview", ConfigType::Bool, &HOVER_OVERVIEW, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"visual_mark_next_page_fraction", ConfigType::Float, &VISUAL_MARK_NEXT_PAGE_FRACTION, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"visual_mark_next_page_threshold", ConfigType::Float, &VISUAL_MARK_NEXT_PAGE_THRESHOLD, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"ui_font", ConfigType::String, &UI_FONT_FACE_NAME, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"middle_click_search_engine", ConfigType::String, &MIDDLE_CLICK_SEARCH_ENGINE, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"shift_middle_click_search_engine", ConfigType::String, &SHIFT_MIDDLE_CLICK_SEARCH_ENGINE, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"startup_commands", ConfigType::String, &STARTUP_COMMANDS, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"font_size", ConfigType::Int, &FONT_SIZE, int_serializer, int_deserializer, nullptr });
    configs.push_back({ L"keyboard_select_font_size", ConfigType::Int, &KEYBOARD_SELECT_FONT_SIZE, int_serializer, int_deserializer, nullptr });
    configs.push_back({ L"status_bar_font_size", ConfigType::Int, &STATUS_BAR_FONT_SIZE, int_serializer, int_deserializer, nullptr });
    configs.push_back({ L"custom_background_color", ConfigType::Color3, CUSTOM_BACKGROUND_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"custom_text_color", ConfigType::Color3, CUSTOM_TEXT_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"rerender_overview", ConfigType::Bool, &RERENDER_OVERVIEW, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"wheel_zoom_on_cursor", ConfigType::Bool, &WHEEL_ZOOM_ON_CURSOR, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"linear_filter", ConfigType::Bool, &LINEAR_TEXTURE_FILTERING, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"display_resolution_scale", ConfigType::Float, &DISPLAY_RESOLUTION_SCALE, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"status_bar_color", ConfigType::Color3, STATUS_BAR_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"status_bar_text_color", ConfigType::Color3, STATUS_BAR_TEXT_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"main_window_size", ConfigType::IVec2, &MAIN_WINDOW_SIZE, ivec2_serializer, ivec2_deserializer, nullptr });
    configs.push_back({ L"helper_window_size", ConfigType::IVec2, &HELPER_WINDOW_SIZE, ivec2_serializer, ivec2_deserializer, nullptr });
    configs.push_back({ L"main_window_move", ConfigType::IVec2, &MAIN_WINDOW_MOVE, ivec2_serializer, ivec2_deserializer, nullptr });
    configs.push_back({ L"helper_window_move", ConfigType::IVec2, &HELPER_WINDOW_MOVE, ivec2_serializer, ivec2_deserializer, nullptr });
    configs.push_back({ L"touchpad_sensitivity", ConfigType::Float, &TOUCHPAD_SENSITIVITY, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"scrollview_sensitivity", ConfigType::Float, &SCROLL_VIEW_SENSITIVITY, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"page_separator_width", ConfigType::Float, &PAGE_SEPARATOR_WIDTH, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"page_separator_color", ConfigType::Color3, PAGE_SEPARATOR_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"single_main_window_size", ConfigType::IVec2, &SINGLE_MAIN_WINDOW_SIZE, ivec2_serializer, ivec2_deserializer, nullptr });
    configs.push_back({ L"single_main_window_move", ConfigType::IVec2, &SINGLE_MAIN_WINDOW_MOVE, ivec2_serializer, ivec2_deserializer, nullptr });
    configs.push_back({ L"fit_to_page_width_ratio", ConfigType::Float, &FIT_TO_PAGE_WIDTH_RATIO, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"collapsed_toc", ConfigType::Bool, &SMALL_TOC, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"ruler_mode", ConfigType::Bool, &RULER_MODE, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"ruler_padding", ConfigType::Float, &RULER_PADDING, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"ruler_x_padding", ConfigType::Float, &RULER_X_PADDING, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"text_summary_url", ConfigType::String, &TEXT_HIGHLIGHT_URL, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"text_summary_should_refine", ConfigType::Bool, &TEXT_SUMMARY_HIGHLIGHT_SHOULD_REFINE, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"text_summary_should_fill", ConfigType::Bool, &TEXT_SUMMARY_HIGHLIGHT_SHOULD_FILL, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"text_summary_context_size", ConfigType::Int, &TEXT_SUMMARY_CONTEXT_SIZE, int_serializer, int_deserializer, nullptr });
    configs.push_back({ L"use_heuristic_if_text_summary_not_available", ConfigType::Bool, &USE_HEURISTIC_IF_TEXT_SUMMARY_NOT_AVAILABLE, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"papers_folder_path", ConfigType::String, &PAPERS_FOLDER_PATH, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"enable_experimental_features", ConfigType::Bool, &ENABLE_EXPERIMENTAL_FEATURES, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"create_table_of_contents_if_not_exists", ConfigType::Bool, &CREATE_TABLE_OF_CONTENTS_IF_NOT_EXISTS, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"max_created_toc_size", ConfigType::Int, &MAX_CREATED_TABLE_OF_CONTENTS_SIZE, int_serializer, int_deserializer, nullptr });
    configs.push_back({ L"force_custom_line_algorithm", ConfigType::Bool, &FORCE_CUSTOM_LINE_ALGORITHM, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"overview_size", ConfigType::FVec2, &OVERVIEW_SIZE, fvec2_serializer, fvec2_deserializer, nullptr });
    configs.push_back({ L"overview_offset", ConfigType::FVec2, &OVERVIEW_OFFSET, fvec2_serializer, fvec2_deserializer, nullptr });
    configs.push_back({ L"ignore_whitespace_in_presentation_mode", ConfigType::Bool, &IGNORE_WHITESPACE_IN_PRESENTATION_MODE, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"exact_highlight_select", ConfigType::Bool, &EXACT_HIGHLIGHT_SELECT, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"show_doc_path", ConfigType::Bool, &SHOW_DOC_PATH, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"fastread_opacity", ConfigType::Float, &FASTREAD_OPACITY, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"should_warn_about_user_key_override", ConfigType::Bool, &SHOULD_WARN_ABOUT_USER_KEY_OVERRIDE, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"single_click_selects_words", ConfigType::Bool, &SINGLE_CLICK_SELECTS_WORDS, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"shift_click_command", ConfigType::String, &SHIFT_CLICK_COMMAND, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"control_click_command", ConfigType::String, &CONTROL_CLICK_COMMAND, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"shift_right_click_command", ConfigType::String, &SHIFT_RIGHT_CLICK_COMMAND, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"control_right_click_command", ConfigType::String, &CONTROL_RIGHT_CLICK_COMMAND, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"use_legacy_keybinds", ConfigType::Bool, &USE_LEGACY_KEYBINDS, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"alt_click_command", ConfigType::String, &ALT_CLICK_COMMAND, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"alt_right_click_command", ConfigType::String, &ALT_RIGHT_CLICK_COMMAND, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"multiline_menus", ConfigType::Bool, &MULTILINE_MENUS, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"start_with_helper_window", ConfigType::Bool, &START_WITH_HELPER_WINDOW, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"prerender_next_page_presentation", ConfigType::Bool, &PRERENDER_NEXT_PAGE, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"emacs_mode_menus", ConfigType::Bool, &EMACS_MODE, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"highlight_middle_click", ConfigType::Bool, &HIGHLIGHT_MIDDLE_CLICK, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"hyperdrive_speed_factor", ConfigType::Bool, &HYPERDRIVE_SPEED_FACTOR, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"smooth_scroll_speed", ConfigType::Float, &SMOOTH_SCROLL_SPEED, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"smooth_scroll_drag", ConfigType::Float, &SMOOTH_SCROLL_DRAG, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"ignore_statusbar_in_presentation_mode", ConfigType::Bool, &IGNORE_STATUSBAR_IN_PRESENTATION_MODE, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"super_fast_search", ConfigType::Bool, &SUPER_FAST_SEARCH, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"show_closest_bookmark_in_statusbar", ConfigType::Bool, &SHOW_CLOSEST_BOOKMARK_IN_STATUSBAR, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"show_close_portal_in_statusbar", ConfigType::Bool, &SHOW_CLOSE_PORTAL_IN_STATUSBAR, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"prerendered_page_count", ConfigType::Int, &PRERENDERED_PAGE_COUNT, int_serializer, int_deserializer, nullptr });
    configs.push_back({ L"case_sensitive_search", ConfigType::Bool, &CASE_SENSITIVE_SEARCH, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"show_document_name_in_statusbar", ConfigType::Bool, &SHOW_DOCUMENT_NAME_IN_STATUSBAR, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"ui_selected_background_color", ConfigType::Color3, UI_SELECTED_BACKGROUND_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"ui_selected_text_color", ConfigType::Color3, UI_SELECTED_TEXT_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"ui_background_color", ConfigType::Color3, STATUS_BAR_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"ui_text_color", ConfigType::Color3, STATUS_BAR_TEXT_COLOR, vec3_serializer, color3_deserializer, color_3_validator });
    configs.push_back({ L"numeric_tags", ConfigType::Bool, &NUMERIC_TAGS, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"highlight_links", ConfigType::Bool, &SHOULD_HIGHLIGHT_LINKS, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"should_highlight_unselected_search", ConfigType::Bool, &SHOULD_HIGHLIGHT_UNSELECTED_SEARCH, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"gamma", ConfigType::Float, &GAMMA, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"fuzzy_searching", ConfigType::Bool, &FUZZY_SEARCHING, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"debug", ConfigType::Bool, &DEBUG, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"highlight_delete_threshold", ConfigType::Float, &HIGHLIGHT_DELETE_THRESHOLD, float_serializer, float_deserializer, nullptr });
    configs.push_back({ L"default_open_file_path", ConfigType::String, &DEFAULT_OPEN_FILE_PATH, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"status_bar_format", ConfigType::String, &STATUS_BAR_FORMAT, string_serializer, string_deserializer, nullptr });
    configs.push_back({ L"inverted_horizontal_scrolling", ConfigType::Bool, &INVERTED_HORIZONTAL_SCROLLING, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"toc_jump_align_top", ConfigType::Bool, &TOC_JUMP_ALIGN_TOP, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"keyboard_select_background_color", ConfigType::Color4, &KEYBOARD_SELECT_BACKGROUND_COLOR, vec4_serializer, vec4_deserializer, nullptr });
    configs.push_back({ L"keyboard_select_text_color", ConfigType::Color4, &KEYBOARD_SELECT_TEXT_COLOR, vec4_serializer, vec4_deserializer, nullptr });
    configs.push_back({ L"autocenter_visual_scroll", ConfigType::Bool, &AUTOCENTER_VISUAL_SCROLL, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"alphabetic_link_tags", ConfigType::Bool, &ALPHABETIC_LINK_TAGS, bool_serializer, bool_deserializer, bool_validator });
    configs.push_back({ L"vimtex_wsl_fix", ConfigType::Bool, &VIMTEX_WSL_FIX, bool_serializer, bool_deserializer, bool_validator });

	std::wstring highlight_config_string = L"highlight_color_a";
	std::wstring search_url_config_string = L"search_url_a";
	std::wstring execute_command_config_string = L"execute_command_a";

	for (char letter = 'a'; letter <= 'z'; letter++) {
		highlight_config_string[highlight_config_string.size() - 1] = letter;
		search_url_config_string[search_url_config_string.size() - 1] = letter;
		execute_command_config_string[execute_command_config_string.size() - 1] = letter;

        configs.push_back({ highlight_config_string, ConfigType::Color3, &HIGHLIGHT_COLORS[(letter - 'a') * 3], vec3_serializer, color3_deserializer, color_3_validator });
        configs.push_back({ search_url_config_string, ConfigType::String, &SEARCH_URLS[letter - 'a'], string_serializer, string_deserializer, nullptr });
        configs.push_back({ execute_command_config_string, ConfigType::String, &EXECUTE_COMMANDS[letter - 'a'], string_serializer, string_deserializer, nullptr });
	}

	deserialize(default_path, auto_path, user_paths);
}

void ConfigManager::persist_config(){
#ifdef SIOYEK_ANDROID
    serialize(android_config_path);
#else
	Path path(L"test.config");
    serialize(path);
#endif

}

void ConfigManager::restore_default(){
#ifdef SIOYEK_ANDROID
    clear_file(android_config_path);
#endif
}

void ConfigManager::clear_file(const Path& path){

    std::wofstream file = open_wofstream(path.get_path());
    file.close();
}

void ConfigManager::serialize(const Path& path) {

    std::wofstream file = open_wofstream(path.get_path());

    for (auto it : configs) {

		if (it.config_type == ConfigType::String) {
			if (((std::wstring*)it.value)->size() == 0) {
				continue;
			}
		}

        std::wstringstream ss;
        file << it.name << " ";
        if (it.get_value()) {
            it.serialize(it.get_value(), ss);
        }
        file << ss.str() << std::endl;
    }

    file.close();
}

void ConfigManager::deserialize_file(const Path& file_path, bool warn_if_not_exists) {

	std::wstring line;
	std::wifstream default_file = open_wifstream(file_path.get_path());
	int line_number = 0;

	if (warn_if_not_exists && (!default_file.good())) {
		std::wcout << "Error: Could not open config file " << file_path.get_path() << std::endl;
	}

	while (std::getline(default_file, line)) {
		line_number++;

		if (line.size() == 0 || line[0] == '#') {
			continue;
		}
        qDebug() << "sioyek: " << QString::fromStdWString(line) << "\n";

		std::wstringstream ss{ line };
		std::wstring conf_name;
		ss >> conf_name;
		//special handling for new_command 
		if (conf_name == L"source") {
			std::wstring path;
			std::getline(ss, path);
			path = strip_string(path);
			if (path.size() > 0) {
				if (path[0] == '.') {
					auto parent_dir = QDir(QString::fromStdWString(file_path.file_parent().get_path()));
					path = parent_dir.absoluteFilePath(QString::fromStdWString(path)).toStdWString();
				}
				if (path[0] == '~') {
					path = QDir::homePath().toStdWString() + path.substr(1, path.size() - 1);
				}

				deserialize_file(path, true);
			}
		}
		else if ((conf_name == L"new_command") || (conf_name == L"new_macro")) {
			std::wstring config_value;
			std::getline(ss, config_value);
			config_value = strip_string(config_value);
			int space_index = config_value.find(L" ");
			std::wstring new_command_name = config_value.substr(0, space_index);
			if (new_command_name[0] == '_') {
				std::wstring command_value = config_value.substr(space_index + 1, config_value.size() - space_index - 1);
				if (conf_name == L"new_command") {
					ADDITIONAL_COMMANDS[new_command_name] = command_value;
				}
				if (conf_name == L"new_macro") {
					ADDITIONAL_MACROS[new_command_name] = command_value;
				}
			}
		}
		else {

			Config* conf = get_mut_config_with_name(conf_name);
			if (conf == nullptr) {
				std::wcout << L"Error: " << conf_name << L" is not a valid configuration name\n";
				continue;
			}

			std::wstring config_value;
			std::getline(ss, config_value);

			std::wstringstream config_value_stream(config_value);

			if ((conf != nullptr) && (conf->validator != nullptr)) {
				if (!conf->validator(config_value)) {
					std::wcout << L"Error in config file " << file_path.get_path() << L" at line " << line_number << L" : " << line << L"\n";
					continue;
				}
			}

			if (conf) {
				auto deserialization_result = conf->deserialize(config_value_stream, conf->value);
				if (deserialization_result != nullptr) {
					conf->value = deserialization_result;
				}
				else {
					std::wcout << L"Error in config file " << file_path.get_path() << L" at line " << line_number << L" : " << line << L"\n";
				}
			}
		}

	}
	default_file.close();
}

void ConfigManager::deserialize(const Path& default_file_path, const Path& auto_path ,const std::vector<Path>& user_file_paths) {

	ADDITIONAL_COMMANDS.clear();

	deserialize_file(default_file_path);
	deserialize_file(auto_path);

	for (const auto& user_file_path : user_file_paths) {
		deserialize_file(user_file_path);
	}
}

std::optional<Path> ConfigManager::get_or_create_user_config_file() {
	if (user_config_paths.size() == 0) {
		return {};
	}

	for (int i = user_config_paths.size() - 1; i >= 0; i--) {
		if (user_config_paths[i].file_exists() ) {
			return user_config_paths[i];
		}
	}
	user_config_paths.back().file_parent().create_directories();
	create_file_if_not_exists(user_config_paths.back().get_path());
	return user_config_paths.back();
}

std::vector<Path> ConfigManager::get_all_user_config_files(){
	std::vector<Path> res;
	for (int i = user_config_paths.size() - 1; i >= 0; i--) {
		if (user_config_paths[i].file_exists()) {
			res.push_back(user_config_paths[i]);
		}
	}
	return  res;
}

std::vector<Config> ConfigManager::get_configs() {
	return configs;
}

void ConfigManager::deserialize_config(std::string config_name, std::wstring config_value) {

	std::wstringstream config_value_stream(config_value);
	Config* conf = get_mut_config_with_name(utf8_decode(config_name));
	auto deserialization_result = conf->deserialize(config_value_stream, conf->value);
	if (deserialization_result != nullptr) {
		conf->value = deserialization_result;
	}

}
