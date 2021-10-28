
//
// Siv3D August 2016 v2 for Visual Studio 2019
// 
// Requirements
// - Visual Studio 2015 (v140) toolset
// - Windows 10 SDK (10.0.17763.0)
//

# include <Siv3D.hpp>


class RaceType {
public:
	enum class Type {
		Win,
		Place,
		Quinella,
		Exacta,
		None
	};

public:
	Type type;

public:
	RaceType() :
		type(Type::None)
	{}

public:
	RaceType(const Type& type) :
		type(type)
	{}

public:
	String to_string() {
		switch (type) {
		case Type::Win:
			return L"単勝";
		case Type::Place:
			return L"複勝";
		case Type::Quinella:
			return L"馬連";
		case Type::Exacta:
			return L"馬単";
		}
		return L"";
	}
};


class HorseName {
public:
	enum class Name {
		A,
		B,
		C,
		D,
		E,
		None
	};

public:
	Name name;

public:
	HorseName() :
		name(Name::None)
	{}

public:
	HorseName(const Name& name) :
		name(name)
	{}

public:
	String to_string() const {
		switch (name) {
		case Name::A:
			return L"A";
		case Name::B:
			return L"B";
		case Name::C:
			return L"C";
		case Name::D:
			return L"D";
		case Name::E:
			return L"E";
		}
		return L"";
	}
};


class BettingTicket {
public:
	RaceType race_type;
	Array<HorseName> horses_name;
	HorseName horse_name_exacta_winner;
	HorseName horse_name_exacta_runner_up;
	int32 betting_handle;

public:
	BettingTicket() :
		race_type(),
		horses_name(),
		horse_name_exacta_winner(),
		horse_name_exacta_runner_up(),
		betting_handle(0)
	{}

public:
	BettingTicket(const RaceType& race_type, const Array<HorseName>& horses_name, const HorseName& horse_name_exacta_winner, const HorseName& horse_name_exacta_runner_up, const int32& betting_handle) :
		race_type(race_type),
		horses_name(horses_name),
		horse_name_exacta_winner(horse_name_exacta_winner),
		horse_name_exacta_runner_up(horse_name_exacta_runner_up),
		betting_handle(betting_handle)
	{}
};


class OddsWin {
public:
	HorseName result;
	double odds;

public:
	OddsWin() :
		result(),
		odds(0.0)
	{}

public:
	OddsWin(const HorseName& horse_name, const double& odds) :
		result(horse_name),
		odds(odds)
	{}
};


class OddsPlace {
public:
	Array<HorseName> results;
	Array<double> odds;

public:
	OddsPlace() :
		results(3),
		odds(3)
	{}

public:
	OddsPlace(const Array<HorseName>& results, const Array<double>& odds) :
		results(results),
		odds(odds)
	{}
};


class OddsQuinella {
public:
	Array<HorseName> results;
	double odds;

public:
	OddsQuinella() :
		results(2),
		odds(0.0)
	{}

public:
	OddsQuinella(const Array<HorseName>& results, const double& odds) :
		results(results),
		odds(odds)
	{}
};



class OddsExacta {
public:
	Array<HorseName> results;
	double odds;

public:
	OddsExacta() :
		results(2),
		odds(0.0)
	{}

public:
	OddsExacta(const Array<HorseName>& results, const double& odds) :
		results(results),
		odds(odds)
	{}
};


class OddsLast {
public:
	OddsWin odds_win;
	OddsPlace odds_place;
	OddsQuinella odds_quinella;
	OddsExacta odds_exacta;

public:
	OddsLast() :
		odds_win(),
		odds_place(),
		odds_quinella(),
		odds_exacta()
	{}

public:
	OddsLast(const OddsWin& odds_win, const OddsPlace& odds_place, const OddsQuinella& odds_quinella, const OddsExacta& odds_exacta) :
		odds_win(odds_win),
		odds_place(odds_place),
		odds_quinella(odds_quinella),
		odds_exacta(odds_exacta)
	{}
};


class Clock {
private:
	String _text;
	Rect _rect;
	Array<Color> _rect_colors;
	const Font _font;
	const Point _font_pos_center;
	const Color _font_color;

public:
	Clock() :
		_text(L"--:--"),
		_rect(0, 0, Window::Size().x, Window::Size().y / 16),
		_rect_colors(4),
		_font(16, L"Rounded M+ 1m regular"),
		_font_pos_center(Window::Size().x / 8 * 7, Window::Size().y / 32),
		_font_color(Palette::Black)
	{
		init();
	}

public:
	void init() {
		_text = L"--:--";
		_rect = Rect(0, 0, Window::Size().x, Window::Size().y / 16);
		_rect_colors.clear();
		_rect_colors.resize(4);
		for (int32 index = 0; index < 4; index++) {
			_rect_colors.at(index) = Color(Palette::White, 255 / 3 * index);
		}
	}

public:
	void update() {
		if (DateTime::Now().milliseconds < 500) {
			_text = Format(L"{:02}:{:02}"_fmt, DateTime::Now().hour, DateTime::Now().minute);
		}
		else {
			_text = Format(L"{:02} {:02}"_fmt, DateTime::Now().hour, DateTime::Now().minute);
		}
	}

public:
	void draw() const {
		_rect.draw({ _rect_colors.at(0), _rect_colors.at(1), _rect_colors.at(2), _rect_colors.at(3) });
		_font.drawCenter(_text, _font_pos_center, _font_color);
	}
};


class SnackBar {
public:
	enum class Flag {
		Information,
		Error
	};

private:
	Array<String> _texts;
	Array<Flag> _flags;
	Rect _rect;
	Vec2 _rect_pos;
	const Vec2 _rect_pos_start;
	const Vec2 _rect_pos_end;
	Color _rect_color;
	const Color _rect_color_information;
	const Color _rect_color_error;
	const Font _font;
	Vec2 _font_pos_center;
	const Vec2 _font_pos_center_start;
	const Vec2 _font_pos_center_end;
	Stopwatch _stopwatch;
	const int32 _stopwatch_duration;
	Sound _sound_information;
	Sound _sound_error;

public:
	SnackBar() :
		_texts(),
		_flags(),
		_rect(0, Window::Size().y, Window::Size().x, Window::Size().y / 16),
		_rect_pos(0.0, Window::Size().y),
		_rect_pos_start(0.0, Window::Size().y),
		_rect_pos_end(0.0, Window::Size().y / 16.0 * 15.0),
		_rect_color(0, 155, 159),
		_rect_color_information(0, 155, 159),
		_rect_color_error(148, 35, 67),
		_font(16, L"Rounded M+ 1m regular"),
		_font_pos_center(Window::Center().x, Window::Size().y + (Window::Size().y / 16.0) / 2.0),
		_font_pos_center_start(Window::Center().x, Window::Size().y + (Window::Size().y / 16.0) / 2.0),
		_font_pos_center_end(Window::Center().x, Window::Size().y / 16.0 * 15.0 + (Window::Size().y / 16.0) / 2.0),
		_stopwatch(),
		_stopwatch_duration(6000),
		_sound_information(L"/64609"),
		_sound_error(L"/64110")
	{
		init();
	}

public:
	void init() {
		_texts.clear();
		_flags.clear();
		_rect = Rect(0, Window::Size().y, Window::Size().x, Window::Size().y / 16);
		_rect_pos = Vec2(0.0, Window::Size().y);
		_rect_color = Color(0, 155, 159);
		_font_pos_center = Vec2(Window::Center().x, Window::Size().y + (Window::Size().y / 16.0) / 2.0);
		_stopwatch.reset();
		_sound_information = Sound(L"/64609");
		_sound_error = Sound(L"/64610");
	}

public:
	void update() {
		if (!_texts.empty() && !_flags.empty()) {
			if (!_stopwatch.isActive() || _stopwatch.isPaused()) {
				_stopwatch.start();
				switch (_flags.front()) {
				case Flag::Information:
					_sound_information.play();
					break;
				case Flag::Error:
					_sound_error.play();
					break;
				}
			}
			if (_stopwatch.ms() < 1000) {
				_rect_pos = EaseOut(_rect_pos_start, _rect_pos_end, Easing::Bounce, _stopwatch.ms() / 1000.0);
				_rect = Rect(_rect_pos.asPoint(), Window::Size().x, Window::Size().y / 16);
				_font_pos_center = EaseOut(_font_pos_center_start, _font_pos_center_end, Easing::Bounce, _stopwatch.ms() / 1000.0);
			}
			else if (1000 <= _stopwatch.ms() && _stopwatch.ms() < _stopwatch_duration - 1000) {
				_rect_pos = _rect_pos_end;
				_rect = Rect(_rect_pos.asPoint(), Window::Size().x, Window::Size().y / 16);
				_font_pos_center = _font_pos_center_end;
			}
			else if (_stopwatch_duration - 1000 <= _stopwatch.ms() && _stopwatch.ms() < _stopwatch_duration) {
				_rect_pos = EaseOut(_rect_pos_end, _rect_pos_start, Easing::Bounce, 1.0 - ((_stopwatch_duration - _stopwatch.ms()) / 1000.0));
				_rect = Rect(_rect_pos.asPoint(), Window::Size().x, Window::Size().y / 16);
				_font_pos_center = EaseOut(_font_pos_center_end, _font_pos_center_start, Easing::Bounce, 1.0 - ((_stopwatch_duration - _stopwatch.ms()) / 1000.0));
			}
			else {
				_texts.erase(_texts.begin());
				_flags.erase(_flags.begin());
				_stopwatch.reset();
			}
			switch (_flags.front()) {
			case Flag::Information:
				_rect_color = _rect_color_information;
				break;
			case Flag::Error:
				_rect_color = _rect_color_error;
				break;
			}
		}
	}

public:
	void draw() const {
		if (!_texts.empty() && !_flags.empty()) {
			_rect.draw(_rect_color);
			_font(_texts.front()).drawCenter(_font_pos_center);
		}
	}

public:
	void show(String text, Flag flag) {
		_texts.push_back(text);
		_flags.push_back(flag);
	}
};


class UI {
public:
	int32 scene;
	Array<OddsWin> odds_win;
	OddsLast odds_last;
	VideoPlayer video_player;
	String scene_0_text;
	Array<Color> scene_0_rect_colors;
	const Font scene_0_font;
	const Point scene_0_font_pos_center;
	const Rect scene_1_rect_table_caption;
	Array<Color> scene_1_rect_table_caption_colors;
	const Font scene_1_font_table_caption;
	const Point scene_1_font_table_caption_pos_center;
	const Rect scene_1_rect_table_header;
	const Color scene_1_rect_table_header_color;
	const Font scene_1_font_table_header;
	const Point scene_1_font_table_header_horse_name_pos_center;
	const Point scene_1_font_table_header_odds_win_pos_center;
	Array<Rect> scene_1_rects_table_row;
	Array<Color> scene_1_rects_table_row_color;
	const Font scene_1_font_table_row;
	Array<Point> scene_1_fonts_table_row_horse_name_pos_center;
	Array<Point> scene_1_fonts_table_row_odds_win_pos_center;
	Array<Color> scene_1_fonts_table_row_odds_win_color;
	const Rect scene_2_rect_table_caption;
	Array<Color> scene_2_rect_table_caption_colors;
	const Font scene_2_font_table_caption;
	const Point scene_2_font_table_caption_pos_center;
	const Rect scene_2_rect_table_header;
	const Color scene_2_rect_table_header_color;
	const Font scene_2_font_table_header;
	const Point scene_2_font_table_header_race_type_pos_center;
	const Point scene_2_font_table_header_horse_name_pos_center;
	const Point scene_2_font_table_header_odds_pos_center;
	const Rect scene_2_rect_table_row_win;
	const Color scene_2_rect_table_row_win_color;
	const Rect scene_2_rect_table_row_place;
	const Color scene_2_rect_table_row_place_color;
	const Rect scene_2_rect_table_row_quinella;
	const Color scene_2_rect_table_row_quinella_color;
	const Rect scene_2_rect_table_row_exacta;
	const Color scene_2_rect_table_row_exacta_color;
	const Font scene_2_font_table_row;
	const Point scene_2_font_table_row_race_type_win_pos_center;
	const Point scene_2_font_table_row_race_type_place_pos_center;
	const Point scene_2_font_table_row_race_type_quinella_pos_center;
	const Point scene_2_font_table_row_race_type_exacta_pos_center;
	const Point scene_2_font_table_row_horse_name_win_pos_center;
	Array<Point> scene_2_fonts_table_row_horse_name_place_pos_center;
	Array<Point> scene_2_fonts_table_row_horse_name_quinella_pos_center;
	Array<Point> scene_2_fonts_table_row_horse_name_exacta_pos_center;
	const Point scene_2_font_table_row_odds_win_pos_center;
	Color scene_2_font_table_row_odds_win_color;
	Array<Point> scene_2_fonts_table_row_odds_place_pos_center;
	Array<Color> scene_2_fonts_table_row_odds_place_color;
	const Point scene_2_font_table_row_odds_quinella_pos_center;
	Color scene_2_font_table_row_odds_quinella_color;
	const Point scene_2_font_table_row_odds_exacta_pos_center;
	Color scene_2_font_table_row_odds_exacta_color;
	SnackBar snackbar;
	Clock clock;

public:
	UI() :
		scene(0),
		odds_win(5),
		odds_last(),
		video_player(L"./background.avi"),
		scene_0_text(L"競馬のプレイ開始を待機中   "),
		scene_0_rect_colors(4),
		scene_0_font(96, L"Rounded M+ 1m regular", FontStyle::Bold),
		scene_0_font_pos_center(Window::Center()),
		scene_1_rect_table_caption(-Window::Size().x / 2, Window::Size().y / 11, Window::Size().x, Window::Size().y / 11 * 2),
		scene_1_rect_table_caption_colors(4),
		scene_1_font_table_caption(96, L"Rounded M+ 1m regular", FontStyle::BoldItalic),
		scene_1_font_table_caption_pos_center(Window::Size().x / 4, Window::Size().y / 11 * 2),
		scene_1_rect_table_header(Window::Size().x / 10, Window::Size().y / 11 * 4, Window::Size().x / 10 * 8, Window::Size().y / 11),
		scene_1_rect_table_header_color(0, 238),
		scene_1_font_table_header(48, L"Rounded M+ 1m regular", FontStyle::Bold),
		scene_1_font_table_header_horse_name_pos_center(Window::Size().x / 10 * 4, Window::Size().y / 11 * 4 + Window::Size().y / 11 / 2),
		scene_1_font_table_header_odds_win_pos_center(Window::Size().x / 10 * 8, Window::Size().y / 11 * 4 + Window::Size().y / 11 / 2),
		scene_1_rects_table_row(5),
		scene_1_rects_table_row_color(5),
		scene_1_font_table_row(48, L"Rounded M+ 1m regular"),
		scene_1_fonts_table_row_horse_name_pos_center(5),
		scene_1_fonts_table_row_odds_win_pos_center(5),
		scene_1_fonts_table_row_odds_win_color(5),
		scene_2_rect_table_caption(-Window::Size().x / 2, Window::Size().y / 14, Window::Size().x, Window::Size().y / 14 * 2),
		scene_2_rect_table_caption_colors(4),
		scene_2_font_table_caption(64, L"Rounded M+ 1m regular", FontStyle::BoldItalic),
		scene_2_font_table_caption_pos_center(Window::Size().x / 4, Window::Size().y / 14 * 2),
		scene_2_rect_table_header(Window::Size().x / 10, Window::Size().y / 14 * 4, Window::Size().x / 10 * 8, Window::Size().y / 14),
		scene_2_rect_table_header_color(0, 238),
		scene_2_font_table_header(32, L"Rounded M+ 1m regular", FontStyle::Bold),
		scene_2_font_table_header_race_type_pos_center(Window::Size().x / 10 * 2, Window::Size().y / 14 * 4 + Window::Size().y / 14 / 2),
		scene_2_font_table_header_horse_name_pos_center(Window::Size().x / 10 * 5, Window::Size().y / 14 * 4 + Window::Size().y / 14 / 2),
		scene_2_font_table_header_odds_pos_center(Window::Size().x / 10 * 8, Window::Size().y / 14 * 4 + Window::Size().y / 14 / 2),
		scene_2_rect_table_row_win(Window::Size().x / 10, Window::Size().y / 14 * 5, Window::Size().x / 10 * 8, Window::Size().y / 14),
		scene_2_rect_table_row_win_color(51, 238),
		scene_2_rect_table_row_place(Window::Size().x / 10, Window::Size().y / 14 * 6, Window::Size().x / 10 * 8, Window::Size().y / 14 * 3),
		scene_2_rect_table_row_place_color(102, 238),
		scene_2_rect_table_row_quinella(Window::Size().x / 10, Window::Size().y / 14 * 9, Window::Size().x / 10 * 8, Window::Size().y / 14 * 2),
		scene_2_rect_table_row_quinella_color(51, 238),
		scene_2_rect_table_row_exacta(Window::Size().x / 10, Window::Size().y / 14 * 11, Window::Size().x / 10 * 8, Window::Size().y / 14 * 2),
		scene_2_rect_table_row_exacta_color(102, 238),
		scene_2_font_table_row(32, L"Rounded M+ 1m regular"),
		scene_2_font_table_row_race_type_win_pos_center(Window::Size().x / 10 * 2, Window::Size().y / 14 * 5 + Window::Size().y / 14 / 2),
		scene_2_font_table_row_race_type_place_pos_center(Window::Size().x / 10 * 2, Window::Size().y / 14 * 7 + Window::Size().y / 14 / 2),
		scene_2_font_table_row_race_type_quinella_pos_center(Window::Size().x / 10 * 2, Window::Size().y / 14 * 10),
		scene_2_font_table_row_race_type_exacta_pos_center(Window::Size().x / 10 * 2, Window::Size().y / 14 * 12),
		scene_2_font_table_row_horse_name_win_pos_center(Window::Size().x / 10 * 5, Window::Size().y / 14 * 5 + Window::Size().y / 14 / 2),
		scene_2_fonts_table_row_horse_name_place_pos_center(3),
		scene_2_fonts_table_row_horse_name_quinella_pos_center(2),
		scene_2_fonts_table_row_horse_name_exacta_pos_center(2),
		scene_2_font_table_row_odds_win_pos_center(Window::Size().x / 10 * 8, Window::Size().y / 14 * 5 + Window::Size().y / 14 / 2),
		scene_2_font_table_row_odds_win_color(Palette::White),
		scene_2_fonts_table_row_odds_place_pos_center(3),
		scene_2_fonts_table_row_odds_place_color(3),
		scene_2_font_table_row_odds_quinella_pos_center(Window::Size().x / 10 * 8, Window::Size().y / 14 * 10),
		scene_2_font_table_row_odds_quinella_color(Palette::White),
		scene_2_font_table_row_odds_exacta_pos_center(Window::Size().x / 10 * 8, Window::Size().y / 14 * 12),
		scene_2_font_table_row_odds_exacta_color(Palette::White),
		snackbar(),
		clock()
	{
		init();
	}

public:
	void init() {
		scene = 0;
		scene_0_text = L"競馬のプレイ開始を待機中   ";
		scene_0_rect_colors.clear();
		scene_0_rect_colors.resize(4);
		for (int32 index = 0; index < 4; index++) {
			scene_0_rect_colors.at(index) = Color(245, 187, 255 / 3 * index);
		}
		odds_win.clear();
		odds_win.resize(5);
		odds_last = OddsLast();
		if (video_player.open(L"./background.avi")) {
			video_player.play();
		}
		else {
			snackbar.show(L"background.aviのオープンに失敗しました :(", SnackBar::Flag::Error);
		}
		scene_1_rect_table_caption_colors.clear();
		scene_1_rect_table_caption_colors.resize(4);
		for (int32 index = 0; index < 4; index++) {
			scene_1_rect_table_caption_colors.at(index) = Color(255 / 3 * index, 119, 228);
		}
		scene_1_rects_table_row.clear();
		scene_1_rects_table_row.resize(5);
		scene_1_rects_table_row_color.clear();
		scene_1_rects_table_row_color.resize(5);
		scene_1_fonts_table_row_horse_name_pos_center.clear();
		scene_1_fonts_table_row_horse_name_pos_center.resize(5);
		scene_1_fonts_table_row_odds_win_pos_center.clear();
		scene_1_fonts_table_row_odds_win_pos_center.resize(5);
		scene_1_fonts_table_row_odds_win_color.clear();
		scene_1_fonts_table_row_odds_win_color.resize(5);
		for (int32 row = 0; row < 5; row++) {
			scene_1_rects_table_row.at(row) = Rect(Window::Size().x / 10, Window::Size().y / 11 * 5 + Window::Size().y / 11 * row, Window::Size().x / 10 * 8, Window::Size().y / 11);
			if (row % 2 == 0) {
				scene_1_rects_table_row_color.at(row) = Color(51, 238);
			}
			else {
				scene_1_rects_table_row_color.at(row) = Color(102, 238);
			}
			scene_1_fonts_table_row_horse_name_pos_center.at(row) = Point(Window::Size().x / 10 * 4, Window::Size().y / 11 * 5 + Window::Size().y / 11 / 2 + Window::Size().y / 11 * row);
			scene_1_fonts_table_row_odds_win_pos_center.at(row) = Point(Window::Size().x / 10 * 8, Window::Size().y / 11 * 5 + Window::Size().y / 11 / 2 + Window::Size().y / 11 * row);
			scene_1_fonts_table_row_odds_win_color.at(row) = Palette::White;
		}
		scene_2_rect_table_caption_colors.clear();
		scene_2_rect_table_caption_colors.resize(4);
		for (int32 index = 0; index < 4; index++) {
			scene_2_rect_table_caption_colors.at(index) = Color(27, 119, 255 / 3 * index);
		}
		scene_2_fonts_table_row_horse_name_place_pos_center.clear();
		scene_2_fonts_table_row_horse_name_place_pos_center.resize(3);
		for (int32 row = 0; row < 3; row++) {
			scene_2_fonts_table_row_horse_name_place_pos_center.at(row) = Point(Window::Size().x / 10 * 5, Window::Size().y / 14 * 6 + Window::Size().y / 14 / 2 + Window::Size().y / 14 * row);
		}
		scene_2_fonts_table_row_horse_name_quinella_pos_center.clear();
		scene_2_fonts_table_row_horse_name_quinella_pos_center.resize(2);
		for (int32 row = 0; row < 2; row++) {
			scene_2_fonts_table_row_horse_name_quinella_pos_center.at(row) = Point(Window::Size().x / 10 * 5, Window::Size().y / 14 * 9 + Window::Size().y / 14 / 2 + Window::Size().y / 14 * row);
		}
		scene_2_fonts_table_row_horse_name_exacta_pos_center.clear();
		scene_2_fonts_table_row_horse_name_exacta_pos_center.resize(2);
		for (int32 row = 0; row < 2; row++) {
			scene_2_fonts_table_row_horse_name_exacta_pos_center.at(row) = Point(Window::Size().x / 10 * 5, Window::Size().y / 14 * 11 + Window::Size().y / 14 / 2 + Window::Size().y / 14 * row);
		}
		scene_2_font_table_row_odds_win_color = Palette::White;
		scene_2_fonts_table_row_odds_place_pos_center.clear();
		scene_2_fonts_table_row_odds_place_pos_center.resize(3);
		scene_2_fonts_table_row_odds_place_color.clear();
		scene_2_fonts_table_row_odds_place_color.resize(3);
		for (int32 row = 0; row < 3; row++) {
			scene_2_fonts_table_row_odds_place_pos_center.at(row) = Point(Window::Size().x / 10 * 8, Window::Size().y / 14 * 6 + Window::Size().y / 14 / 2 + Window::Size().y / 14 * row);
			scene_2_fonts_table_row_odds_place_color.at(row) = Palette::White;
		}
	}

public:
	void update() {
		if (video_player.isOpened()) {
			video_player.update();
		}
		if (DateTime::Now().second % 2 == 0) {
			if (DateTime::Now().milliseconds < 500) {
				scene_0_text = L"競馬のプレイ開始を待機中   ";
			}
			else {
				scene_0_text = L"競馬のプレイ開始を待機中.  ";
			}
		}
		else {
			if (DateTime::Now().milliseconds < 500) {
				scene_0_text = L"競馬のプレイ開始を待機中.. ";
			}
			else {
				scene_0_text = L"競馬のプレイ開始を待機中...";
			}
		}
		snackbar.update();
		clock.update();
	}

public:
	void draw() const {
		if (video_player.isOpened()) {
			video_player.getFrameTexture().draw();
		}
		switch (scene) {
		case 0:
			scene_0_font(scene_0_text).regionCenter(scene_0_font_pos_center).draw({ scene_0_rect_colors.at(0), scene_0_rect_colors.at(1), scene_0_rect_colors.at(2), scene_0_rect_colors.at(3) });
			scene_0_font(scene_0_text).drawCenter(scene_0_font_pos_center);
			break;
		case 1:
			scene_1_rect_table_caption.shearedX(45.0).draw({ scene_1_rect_table_caption_colors.at(0), scene_1_rect_table_caption_colors.at(1),
				scene_1_rect_table_caption_colors.at(2), scene_1_rect_table_caption_colors.at(3) });
			scene_1_font_table_caption.drawCenter(L"単勝オッズ", scene_1_font_table_caption_pos_center);
			scene_1_rect_table_header.draw(scene_1_rect_table_header_color);
			scene_1_font_table_header.drawCenter(L"馬名", scene_1_font_table_header_horse_name_pos_center);
			scene_1_font_table_header.drawCenter(L"単勝オッズ", scene_1_font_table_header_odds_win_pos_center);
			for (int32 row = 0; row < 5; row++) {
				scene_1_rects_table_row.at(row).draw(scene_1_rects_table_row_color.at(row));
				scene_1_font_table_row.drawCenter(odds_win.at(row).result.to_string(), scene_1_fonts_table_row_horse_name_pos_center.at(row));
				scene_1_font_table_row.drawCenter(Format(L"{:.1f}"_fmt, odds_win.at(row).odds), scene_1_fonts_table_row_odds_win_pos_center.at(row), scene_1_fonts_table_row_odds_win_color.at(row));
			}
			break;
		case 2:
			scene_2_rect_table_caption.shearedX(45.0).draw({ scene_2_rect_table_caption_colors.at(0), scene_2_rect_table_caption_colors.at(1),
				scene_2_rect_table_caption_colors.at(2), scene_2_rect_table_caption_colors.at(3) });
			scene_2_font_table_caption.drawCenter(L"最終オッズ", scene_2_font_table_caption_pos_center);
			scene_2_rect_table_header.draw(scene_2_rect_table_header_color);
			scene_2_font_table_header.drawCenter(L"レース式別", scene_2_font_table_header_race_type_pos_center);
			scene_2_font_table_header.drawCenter(L"馬名", scene_2_font_table_header_horse_name_pos_center);
			scene_2_font_table_header.drawCenter(L"オッズ", scene_2_font_table_header_odds_pos_center);
			scene_2_rect_table_row_win.draw(scene_2_rect_table_row_win_color);
			scene_2_rect_table_row_place.draw(scene_2_rect_table_row_place_color);
			scene_2_rect_table_row_quinella.draw(scene_2_rect_table_row_quinella_color);
			scene_2_rect_table_row_exacta.draw(scene_2_rect_table_row_exacta_color);
			RaceType race_type;
			race_type.type = RaceType::Type::Win;
			scene_2_font_table_row.drawCenter(race_type.to_string(), scene_2_font_table_row_race_type_win_pos_center);
			race_type.type = RaceType::Type::Place;
			scene_2_font_table_row.drawCenter(race_type.to_string(), scene_2_font_table_row_race_type_place_pos_center);
			race_type.type = RaceType::Type::Quinella;
			scene_2_font_table_row.drawCenter(race_type.to_string(), scene_2_font_table_row_race_type_quinella_pos_center);
			race_type.type = RaceType::Type::Exacta;
			scene_2_font_table_row.drawCenter(race_type.to_string(), scene_2_font_table_row_race_type_exacta_pos_center);
			scene_2_font_table_row.drawCenter(odds_last.odds_win.result.to_string(), scene_2_font_table_row_horse_name_win_pos_center);
			for (int32 row = 0; row < 3; row++) {
				scene_2_font_table_row.drawCenter(odds_last.odds_place.results.at(row).to_string(), scene_2_fonts_table_row_horse_name_place_pos_center.at(row));
			}
			for (int32 row = 0; row < 2; row++) {
				scene_2_font_table_row.drawCenter(odds_last.odds_quinella.results.at(row).to_string(), scene_2_fonts_table_row_horse_name_quinella_pos_center.at(row));
			}
			for (int32 row = 0; row < 2; row++) {
				scene_2_font_table_row.drawCenter(odds_last.odds_exacta.results.at(row).to_string(), scene_2_fonts_table_row_horse_name_exacta_pos_center.at(row));
			}
			scene_2_font_table_row.drawCenter(Format(L"{:.1f}"_fmt, odds_last.odds_win.odds), scene_2_font_table_row_odds_win_pos_center, scene_2_font_table_row_odds_win_color);
			for (int32 row = 0; row < 3; row++) {
				scene_2_font_table_row.drawCenter(Format(L"{:.1f}"_fmt, odds_last.odds_place.odds.at(row)), scene_2_fonts_table_row_odds_place_pos_center.at(row), scene_2_fonts_table_row_odds_place_color.at(row));
			}
			scene_2_font_table_row.drawCenter(Format(L"{:.1f}"_fmt, odds_last.odds_quinella.odds), scene_2_font_table_row_odds_quinella_pos_center, scene_2_font_table_row_odds_quinella_color);
			scene_2_font_table_row.drawCenter(Format(L"{:.1f}"_fmt, odds_last.odds_exacta.odds), scene_2_font_table_row_odds_exacta_pos_center, scene_2_font_table_row_odds_exacta_color);
			break;
		}
		snackbar.draw();
		clock.draw();
	}
};


class Backend {
private:
	INIReader _ini_reader_odds_win;
	INIReader _ini_reader_odds_last;

public:
	Backend(UI& ui) :
		_ini_reader_odds_win(L"./runs/odds_win.ini"),
		_ini_reader_odds_last(L"./runs/odds_last.ini")
	{
		init(ui);
	}

public:
	void init(UI& ui) {
		if (!_ini_reader_odds_win.open(L"./runs/odds_win.ini")) {
			MessageBox::Show(L"./runs/odds_win.iniのオープンに失敗しました :(");
			System::Exit();
			return;
		}
		if (!_ini_reader_odds_last.open(L"./runs/odds_last.ini")) {
			MessageBox::Show(L"./runs/odds_last.iniのオープンに失敗しました :(");
			System::Exit();
			return;
		}
		_init_odds_win(ui);
		_init_odds_last(ui);
		ui.scene = 0;
		if (!_ini_reader_odds_win.isEmpty()) {
			ui.scene = 1;
		}
		if (!_ini_reader_odds_last.isEmpty()) {
			ui.scene = 2;
		}
	}

public:
	void update(UI& ui) {
		if (_ini_reader_odds_win.hasChanged()) {
			if (_ini_reader_odds_win.reload()) {
				_update_odds_win(ui);
				ui.scene = 0;
				if (!_ini_reader_odds_win.isEmpty()) {
					ui.scene = 1;
					ui.snackbar.show(L"単勝オッズデータが更新されました。", SnackBar::Flag::Information);
				}
				else {
					ui.snackbar.show(L"単勝オッズデータがクリアされました。", SnackBar::Flag::Information);
				}
				if (!_ini_reader_odds_last.isEmpty()) {
					ui.scene = 2;
				}
			}
			else {
				ui.snackbar.show(L"./runs/odds_win.iniの再読み込みに失敗しました :(", SnackBar::Flag::Error);
			}
		}
		if (_ini_reader_odds_last.hasChanged()) {
			if (_ini_reader_odds_last.reload()) {
				_update_odds_last(ui);
				ui.scene = 0;
				if (!_ini_reader_odds_win.isEmpty()) {
					ui.scene = 1;
				}
				if (!_ini_reader_odds_last.isEmpty()) {
					ui.scene = 2;
					ui.snackbar.show(L"最終オッズデータが更新されました。", SnackBar::Flag::Information);
				}
				else {
					ui.snackbar.show(L"最終オッズデータがクリアされました。", SnackBar::Flag::Information);
				}
			}
			else {
				ui.snackbar.show(L"./runs/odds_last.iniの再読み込みに失敗しました :(", SnackBar::Flag::Error);
			}
		}
	}

private:
	void _init_odds_win(UI& ui) {
		double odds_min = DBL_MAX;
		double odds_max = 0.0;
		for (int32 index = 0; index < 5; index++) {
			ui.odds_win.at(index).result.name = from_string(_ini_reader_odds_win.get<String>(Format(L"OddsWin_HorseName.{}"_fmt, index)));
			ui.odds_win.at(index).odds = _ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index));
			odds_min = Min(_ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index)), odds_min);
			odds_max = Max(_ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index)), odds_max);
		}
		for (int32 index = 0; index < 5; index++) {
			if (odds_min != odds_max) {
				if (_ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index)) < (odds_min + odds_max) / 2.0) {
					ui.scene_1_fonts_table_row_odds_win_color.at(index) = HSV(38760.0 / 113.0, (113.0 / 148.0) * (((odds_min + odds_max) / 2.0 - _ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index))) / ((odds_min + odds_max) / 2.0 - odds_min)), (148.0 + (255.0 - 148.0) * (_ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index)) - odds_min) / ((odds_min + odds_max) / 2.0 - odds_min)) / 255.0);
				}
				else {
					ui.scene_1_fonts_table_row_odds_win_color.at(index) = HSV(9620.0 / 53.0, (_ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index)) - (odds_min + odds_max) / 2.0) / (odds_max - (odds_min + odds_max) / 2.0), (53.0 + (255.0 - 53.0) * (odds_max - _ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index))) / (odds_max - (odds_min + odds_max) / 2.0)) / 85.0);
				}
			}
			else {
				ui.scene_1_fonts_table_row_odds_win_color.at(index) = Palette::White;
			}
		}
	}

private:
	void _init_odds_last(UI& ui) {
		double odds_min = DBL_MAX;
		double odds_max = 0.0;
		ui.odds_last.odds_win.result.name = from_string(_ini_reader_odds_last.get<String>(Format(L"OddsWin_HorseName.{}"_fmt, 0)));
		ui.odds_last.odds_win.odds = _ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0));
		odds_min = Min(_ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0)), odds_min);
		odds_max = Max(_ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0)), odds_max);
		for (int32 order_of_finish = 0; order_of_finish < 3; order_of_finish++) {
			ui.odds_last.odds_place.results.at(order_of_finish).name = from_string(_ini_reader_odds_last.get<String>(Format(L"OddsPlace_HorseName.{}"_fmt, order_of_finish)));
			ui.odds_last.odds_place.odds.at(order_of_finish) = _ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish));
			odds_min = Min(_ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish)), odds_min);
			odds_max = Max(_ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish)), odds_max);
		}
		for (int32 order_of_finish = 0; order_of_finish < 2; order_of_finish++) {
			ui.odds_last.odds_quinella.results.at(order_of_finish).name = from_string(_ini_reader_odds_last.get<String>(Format(L"OddsQuinella_HorseName.{}"_fmt, order_of_finish)));
		}
		ui.odds_last.odds_quinella.odds = _ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0));
		odds_min = Min(_ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0)), odds_min);
		odds_max = Max(_ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0)), odds_max);
		for (int32 order_of_finish = 0; order_of_finish < 2; order_of_finish++) {
			ui.odds_last.odds_exacta.results.at(order_of_finish).name = from_string(_ini_reader_odds_last.get<String>(Format(L"OddsExacta_HorseName.{}"_fmt, order_of_finish)));
		}
		ui.odds_last.odds_exacta.odds = _ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0));
		odds_min = Min(_ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0)), odds_min);
		odds_max = Max(_ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0)), odds_max);
		if (odds_min != odds_max) {
			if (_ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0)) < (odds_min + odds_max) / 2.0) {
				ui.scene_2_font_table_row_odds_win_color = HSV(38760.0 / 113.0, (113.0 / 148.0) * (((odds_min + odds_max) / 2.0 - _ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0))) / ((odds_min + odds_max) / 2.0 - odds_min)), (148.0 + (255.0 - 148.0) * (_ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0)) - odds_min) / ((odds_min + odds_max) / 2.0 - odds_min)) / 255.0);
			}
			else {
				ui.scene_2_font_table_row_odds_win_color = HSV(9620.0 / 53.0, (_ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0)) - (odds_min + odds_max) / 2.0) / (odds_max - (odds_min + odds_max) / 2.0), (53.0 + (255.0 - 53.0) * (odds_max - _ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0))) / (odds_max - (odds_min + odds_max) / 2.0)) / 85.0);
			}
			for (int32 order_of_finish = 0; order_of_finish < 3; order_of_finish++) {
				if (_ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish)) < (odds_min + odds_max) / 2.0) {
					ui.scene_2_fonts_table_row_odds_place_color.at(order_of_finish) = HSV(38760.0 / 113.0, (113.0 / 148.0) * (((odds_min + odds_max) / 2.0 - _ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish))) / ((odds_min + odds_max) / 2.0 - odds_min)), (148.0 + (255.0 - 148.0) * (_ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish)) - odds_min) / ((odds_min + odds_max) / 2.0 - odds_min)) / 255.0);
				}
				else {
					ui.scene_2_fonts_table_row_odds_place_color.at(order_of_finish) = HSV(9620.0 / 53.0, (_ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish)) - (odds_min + odds_max) / 2.0) / (odds_max - (odds_min + odds_max) / 2.0), (53.0 + (255.0 - 53.0) * (odds_max - _ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish))) / (odds_max - (odds_min + odds_max) / 2.0)) / 85.0);
				}
			}
			if (_ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0)) < (odds_min + odds_max) / 2.0) {
				ui.scene_2_font_table_row_odds_quinella_color = HSV(38760.0 / 113.0, (113.0 / 148.0) * (((odds_min + odds_max) / 2.0 - _ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0))) / ((odds_min + odds_max) / 2.0 - odds_min)), (148.0 + (255.0 - 148.0) * (_ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0)) - odds_min) / ((odds_min + odds_max) / 2.0 - odds_min)) / 255.0);
			}
			else {
				ui.scene_2_font_table_row_odds_quinella_color = HSV(9620.0 / 53.0, (_ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0)) - (odds_min + odds_max) / 2.0) / (odds_max - (odds_min + odds_max) / 2.0), (53.0 + (255.0 - 53.0) * (odds_max - _ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0))) / (odds_max - (odds_min + odds_max) / 2.0)) / 85.0);
			}
			if (_ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0)) < (odds_min + odds_max) / 2.0) {
				ui.scene_2_font_table_row_odds_exacta_color = HSV(38760.0 / 113.0, (113.0 / 148.0) * (((odds_min + odds_max) / 2.0 - _ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0))) / ((odds_min + odds_max) / 2.0 - odds_min)), (148.0 + (255.0 - 148.0) * (_ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0)) - odds_min) / ((odds_min + odds_max) / 2.0 - odds_min)) / 255.0);
			}
			else {
				ui.scene_2_font_table_row_odds_exacta_color = HSV(9620.0 / 53.0, (_ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0)) - (odds_min + odds_max) / 2.0) / (odds_max - (odds_min + odds_max) / 2.0), (53.0 + (255.0 - 53.0) * (odds_max - _ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0))) / (odds_max - (odds_min + odds_max) / 2.0)) / 85.0);
			}
		}
		else {
			ui.scene_2_font_table_row_odds_win_color = Palette::White;
			for (int32 order_of_finish = 0; order_of_finish < 3; order_of_finish++) {
				ui.scene_2_fonts_table_row_odds_place_color.at(order_of_finish) = Palette::White;
			}
			ui.scene_2_font_table_row_odds_quinella_color = Palette::White;
			ui.scene_2_font_table_row_odds_exacta_color = Palette::White;
		}
	}

private:
	void _update_odds_win(UI& ui) {
		double odds_min = DBL_MAX;
		double odds_max = 0.0;
		for (int32 index = 0; index < 5; index++) {
			ui.odds_win.at(index).result.name = from_string(_ini_reader_odds_win.get<String>(Format(L"OddsWin_HorseName.{}"_fmt, index)));
			ui.odds_win.at(index).odds = _ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index));
			odds_min = Min(_ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index)), odds_min);
			odds_max = Max(_ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index)), odds_max);
		}
		for (int32 index = 0; index < 5; index++) {
			if (odds_min != odds_max) {
				if (_ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index)) < (odds_min + odds_max) / 2.0) {
					ui.scene_1_fonts_table_row_odds_win_color.at(index) = HSV(38760.0 / 113.0, (113.0 / 148.0) * (((odds_min + odds_max) / 2.0 - _ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index))) / ((odds_min + odds_max) / 2.0 - odds_min)), (148.0 + (255.0 - 148.0) * (_ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index)) - odds_min) / ((odds_min + odds_max) / 2.0 - odds_min)) / 255.0);
				}
				else {
					ui.scene_1_fonts_table_row_odds_win_color.at(index) = HSV(9620.0 / 53.0, (_ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index)) - (odds_min + odds_max) / 2.0) / (odds_max - (odds_min + odds_max) / 2.0), (53.0 + (255.0 - 53.0) * (odds_max - _ini_reader_odds_win.get<double>(Format(L"OddsWin_Odds.{}"_fmt, index))) / (odds_max - (odds_min + odds_max) / 2.0)) / 85.0);
				}
			}
			else {
				ui.scene_1_fonts_table_row_odds_win_color.at(index) = Palette::White;
			}
		}
	}

private:
	void _update_odds_last(UI& ui) {
		double odds_min = DBL_MAX;
		double odds_max = 0.0;
		ui.odds_last.odds_win.result.name = from_string(_ini_reader_odds_last.get<String>(Format(L"OddsWin_HorseName.{}"_fmt, 0)));
		ui.odds_last.odds_win.odds = _ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0));
		odds_min = Min(_ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0)), odds_min);
		odds_max = Max(_ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0)), odds_max);
		for (int32 order_of_finish = 0; order_of_finish < 3; order_of_finish++) {
			ui.odds_last.odds_place.results.at(order_of_finish).name = from_string(_ini_reader_odds_last.get<String>(Format(L"OddsPlace_HorseName.{}"_fmt, order_of_finish)));
			ui.odds_last.odds_place.odds.at(order_of_finish) = _ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish));
			odds_min = Min(_ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish)), odds_min);
			odds_max = Max(_ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish)), odds_max);
		}
		for (int32 order_of_finish = 0; order_of_finish < 2; order_of_finish++) {
			ui.odds_last.odds_quinella.results.at(order_of_finish).name = from_string(_ini_reader_odds_last.get<String>(Format(L"OddsQuinella_HorseName.{}"_fmt, order_of_finish)));
		}
		ui.odds_last.odds_quinella.odds = _ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0));
		odds_min = Min(_ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0)), odds_min);
		odds_max = Max(_ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0)), odds_max);
		for (int32 order_of_finish = 0; order_of_finish < 2; order_of_finish++) {
			ui.odds_last.odds_exacta.results.at(order_of_finish).name = from_string(_ini_reader_odds_last.get<String>(Format(L"OddsExacta_HorseName.{}"_fmt, order_of_finish)));
		}
		ui.odds_last.odds_exacta.odds = _ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0));
		odds_min = Min(_ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0)), odds_min);
		odds_max = Max(_ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0)), odds_max);
		if (odds_min != odds_max) {
			if (_ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0)) < (odds_min + odds_max) / 2.0) {
				ui.scene_2_font_table_row_odds_win_color = HSV(38760.0 / 113.0, (113.0 / 148.0) * (((odds_min + odds_max) / 2.0 - _ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0))) / ((odds_min + odds_max) / 2.0 - odds_min)), (148.0 + (255.0 - 148.0) * (_ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0)) - odds_min) / ((odds_min + odds_max) / 2.0 - odds_min)) / 255.0);
			}
			else {
				ui.scene_2_font_table_row_odds_win_color = HSV(9620.0 / 53.0, (_ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0)) - (odds_min + odds_max) / 2.0) / (odds_max - (odds_min + odds_max) / 2.0), (53.0 + (255.0 - 53.0) * (odds_max - _ini_reader_odds_last.get<double>(Format(L"OddsWin_Odds.{}"_fmt, 0))) / (odds_max - (odds_min + odds_max) / 2.0)) / 85.0);
			}
			for (int32 order_of_finish = 0; order_of_finish < 3; order_of_finish++) {
				if (_ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish)) < (odds_min + odds_max) / 2.0) {
					ui.scene_2_fonts_table_row_odds_place_color.at(order_of_finish) = HSV(38760.0 / 113.0, (113.0 / 148.0) * (((odds_min + odds_max) / 2.0 - _ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish))) / ((odds_min + odds_max) / 2.0 - odds_min)), (148.0 + (255.0 - 148.0) * (_ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish)) - odds_min) / ((odds_min + odds_max) / 2.0 - odds_min)) / 255.0);
				}
				else {
					ui.scene_2_fonts_table_row_odds_place_color.at(order_of_finish) = HSV(9620.0 / 53.0, (_ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish)) - (odds_min + odds_max) / 2.0) / (odds_max - (odds_min + odds_max) / 2.0), (53.0 + (255.0 - 53.0) * (odds_max - _ini_reader_odds_last.get<double>(Format(L"OddsPlace_Odds.{}"_fmt, order_of_finish))) / (odds_max - (odds_min + odds_max) / 2.0)) / 85.0);
				}
			}
			if (_ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0)) < (odds_min + odds_max) / 2.0) {
				ui.scene_2_font_table_row_odds_quinella_color = HSV(38760.0 / 113.0, (113.0 / 148.0) * (((odds_min + odds_max) / 2.0 - _ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0))) / ((odds_min + odds_max) / 2.0 - odds_min)), (148.0 + (255.0 - 148.0) * (_ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0)) - odds_min) / ((odds_min + odds_max) / 2.0 - odds_min)) / 255.0);
			}
			else {
				ui.scene_2_font_table_row_odds_quinella_color = HSV(9620.0 / 53.0, (_ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0)) - (odds_min + odds_max) / 2.0) / (odds_max - (odds_min + odds_max) / 2.0), (53.0 + (255.0 - 53.0) * (odds_max - _ini_reader_odds_last.get<double>(Format(L"OddsQuinella_Odds.{}"_fmt, 0))) / (odds_max - (odds_min + odds_max) / 2.0)) / 85.0);
			}
			if (_ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0)) < (odds_min + odds_max) / 2.0) {
				ui.scene_2_font_table_row_odds_exacta_color = HSV(38760.0 / 113.0, (113.0 / 148.0) * (((odds_min + odds_max) / 2.0 - _ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0))) / ((odds_min + odds_max) / 2.0 - odds_min)), (148.0 + (255.0 - 148.0) * (_ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0)) - odds_min) / ((odds_min + odds_max) / 2.0 - odds_min)) / 255.0);
			}
			else {
				ui.scene_2_font_table_row_odds_exacta_color = HSV(9620.0 / 53.0, (_ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0)) - (odds_min + odds_max) / 2.0) / (odds_max - (odds_min + odds_max) / 2.0), (53.0 + (255.0 - 53.0) * (odds_max - _ini_reader_odds_last.get<double>(Format(L"OddsExacta_Odds.{}"_fmt, 0))) / (odds_max - (odds_min + odds_max) / 2.0)) / 85.0);
			}
		}
		else {
			ui.scene_2_font_table_row_odds_win_color = Palette::White;
			for (int32 order_of_finish = 0; order_of_finish < 3; order_of_finish++) {
				ui.scene_2_fonts_table_row_odds_place_color.at(order_of_finish) = Palette::White;
			}
			ui.scene_2_font_table_row_odds_quinella_color = Palette::White;
			ui.scene_2_font_table_row_odds_exacta_color = Palette::White;
		}
	}

private:
	HorseName::Name from_string(const String name) {
		HorseName _horse_name;
		_horse_name.name = HorseName::Name::A;
		if (name == _horse_name.to_string()) {
			return HorseName::Name::A;
		}
		_horse_name.name = HorseName::Name::B;
		if (name == _horse_name.to_string()) {
			return HorseName::Name::B;
		}
		_horse_name.name = HorseName::Name::C;
		if (name == _horse_name.to_string()) {
			return HorseName::Name::C;
		}
		_horse_name.name = HorseName::Name::D;
		if (name == _horse_name.to_string()) {
			return HorseName::Name::D;
		}
		_horse_name.name = HorseName::Name::E;
		if (name == _horse_name.to_string()) {
			return HorseName::Name::E;
		}
		return HorseName::Name::None;
	}
};


void Main() {
	Window::SetTitle(L"5I Horse Race Manager");
	Graphics::SetBackground(Color(204));
	ScreenCapture::EnableScreenshot(false);
	System::SetExitEvent(WindowEvent::Manual);
	Window::SetStyle(WindowStyle::Sizeable);
	Window::Maximize();
	System::Update();;
	FontManager::Register(L"/64608");
	UI ui;
	Backend backend(ui);
	while (System::Update()) {
		backend.update(ui);
		ui.update();
		ui.draw();
	}
}
