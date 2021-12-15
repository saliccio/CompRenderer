#pragma once

namespace CompRenderer {
	class Clickable {
	protected:
		bool clickedInPreviousFrame;

	public:
		virtual ~Clickable() = 0;

		virtual void onClick();
	};
}