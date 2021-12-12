#pragma once

#define CHWND_EXCEPT(hr) Window::WindowException(__LINE__, __FILE__, hr)
#define CHWND_LAST_EXCEPT() Window::WindowException(__LINE__, __FILE__, GetLastError())
#define CHWND_NOGFX_EXCEPT() Window::NoGFXException( __LINE__,__FILE__ )
