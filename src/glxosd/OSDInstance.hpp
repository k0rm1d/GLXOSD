/*
 * Copyright (C) 2013 Nick Guletskii
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef OSDINSTANCE_HPP_
#define OSDINSTANCE_HPP_
#include <GL/gl.h>
#include <FTGL/ftgl.h>
#include <boost/format.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost/any.hpp>
#include <string>
#include <map>
namespace glxosd {
class OSDInstance {
private:
	std::map<std::string, boost::any> configuration;
	int currentFrameCount; // The number of frames from the last FPS calculation
	long previousTime; //The time of the previous FPS calculation
	double framesPerSecond; //Current FPS
	FTGLExtrdFont* font;
	std::string osdText;
	void update(long currentMilliseconds);
public:
	OSDInstance();
	void render(unsigned int width, unsigned int height);
	template<typename T>
	T getProperty(std::string key) {
		if (configuration.find(key) == configuration.end()) {
			throw std::runtime_error("Missing GLXOSD property " + key);
		}
		boost::any obj = configuration[key];
		if (obj.type() != typeid(T)) {
			throw std::runtime_error(
					"GLXOSD property " + key
							+ " has an incorrect type! Expected "
							+ typeid(T).name() + ", got " + obj.type().name());
		}
		T val = boost::any_cast<T>(obj);
		return val;
	}
	virtual ~OSDInstance();
};
}
#endif