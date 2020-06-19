#pragma once

namespace Cajo {

	class Shader {
	public:
		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};

}