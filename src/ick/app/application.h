#pragma once

namespace ick{
	class Application {
		bool running_;
	public:
		Application();
		virtual ~Application();
		
		void Launch();
		void Terminate();
	};
}
