#pragma once
#ifndef   DIA_QTVIEW_HPP
#define   DIA_QTVIEW_HPP


// standard library
#include <memory>
#include <optional>
#include <string_view>


namespace dia::details
{
	using std::optional;
	using std::string_view;
	using std::unique_ptr;


	// view implementation using Qt
	class QtView
	{
		class Impl;

	private:
		explicit QtView(int& argc, char**& argv);

	public: // creation and destruction of objects
		static auto build(int& argc, char**& argv) noexcept -> optional<QtView>;
		~QtView() noexcept; // no virtual

	public: // movable and non-copyable
		QtView(QtView&&) noexcept;
		QtView& operator=(QtView&&) noexcept;

		QtView(QtView const&) = delete;
		QtView& operator=(QtView const&) = delete;

	public: // set paths
		auto set_log_path(string_view path) noexcept -> bool;
		void invalidate_log_path() noexcept;

		auto set_config_path(string_view path) noexcept -> bool;
		void invalidate_config_path() noexcept;

		auto set_plugins_path(string_view path) noexcept -> bool;
		void invalidate_plugins_path() noexcept;

	public: // main event loop and executed code generation
		auto wait() noexcept -> bool;
		auto code() noexcept -> int;

	private: // PIMPL
		unique_ptr<Impl> m_impl;
	};
}

namespace dia
{ using details::QtView; }


#endif // DIA_QTVIEW_HPP
