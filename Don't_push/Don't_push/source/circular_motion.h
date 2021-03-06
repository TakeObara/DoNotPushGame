#pragma once
#include "define.h"
#include <dxlibex/basic_types.hpp>
#include <dxlibex/graph2d.hpp>
#include <array>
#include <cstdint>

class obj_info
{
public:
	obj_info(const dxle::pointi& first_p, const dxle::texture2d* img_normal, const dxle::texture2d* img_fall);
	obj_info(const obj_info& o) = delete;
	obj_info(obj_info&& o) NOEXCEPT;
	obj_info& operator=(const obj_info&) = delete;
	obj_info& operator=(obj_info&&) = delete;
	void change_img(int no = -1) NOEXCEPT;
	bool draw(bool Trans_flag = true) const NOEXCEPT;
	void state_init() NOEXCEPT;
	const dxle::pointi& get_fitst_pos() const NOEXCEPT;
	dxle::pointi& get_pos() NOEXCEPT;
	const dxle::pointi& get_pos() const NOEXCEPT;
	dxle::sizei get_obj_size() const NOEXCEPT;
	dxle::pointi calc_first_bottom_right_pos() const NOEXCEPT;
	dxle::pointi distance_from_first() const NOEXCEPT;
	bool is_fallen() const NOEXCEPT;

	size_t m_fall_frame;
private:
	const dxle::pointi m_first_pos_;
	dxle::pointi m_p_;
	std::array<const dxle::texture2d*, 2> m_img_;
	uint8_t m_current_img_no_;
};
int distance(const obj_info& l, const obj_info& r) NOEXCEPT;
int distance_first(const obj_info& l, const obj_info& r) NOEXCEPT;
double bouninngenn_moving_distance(const obj_info& bouninngenn_a, const obj_info& bouninngenn_b) NOEXCEPT;
void extruder(obj_info& move_target, const int v) NOEXCEPT;
void extruder(obj_info& move_target, const obj_info& move_cause) NOEXCEPT;
class circular_motion
{
public:
	circular_motion() = delete;
	circular_motion(const dxle::pointi& center_pos, const dxle::pointi& first_pos, double angular_v, const dxle::texture2d& img_normal, const dxle::texture2d& img_fall) NOEXCEPT;
	circular_motion(const circular_motion&) = delete;
	circular_motion(circular_motion&&) = delete;
	circular_motion& operator=(const circular_motion&) = delete;
	circular_motion& operator=(circular_motion&&) = delete;
	bool update() NOEXCEPT;
	bool draw() const;
	dxle::pointi get_pos() const NOEXCEPT;
	const obj_info& get_obj() const NOEXCEPT;
private:
	const dxle::pointi m_center_;
	const double m_r_;
	const double m_first_rad_;
	double m_angular_v_;// rad./sec. Dextrorotation(右回り。yは下向き正)
	obj_info m_obj_;
	size_t m_t_;
};
