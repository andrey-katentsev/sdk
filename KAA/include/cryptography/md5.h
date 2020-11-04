//
// File: md5.h
// Description: the MD5 message-digest algorithm
// Created: August 18, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <cstdint>

namespace KAA
{
	namespace cryptography
	{
		class hash;
		class provider;

		struct md5_t
		{
			union
			{
				uint64_t qword[2];
				uint32_t dword[4];
				uint16_t word[8];
				uint8_t byte[16];
			};
		};

		class md5
		{
		public:
			md5();
			md5(md5&&) = delete;
			md5(const md5&) = delete;
			md5(const std::vector<uint8_t>& data);
			md5& operator = (md5&&) = delete;
			md5& operator = (const md5&) = delete;
			~md5();

			void add_data(const std::vector<uint8_t>& data);
			md5_t complete(void);

		private:
			std::unique_ptr<provider> csp; // cryptographic service provider
			std::unique_ptr<hash> hash;
		};

		bool operator == (const md5_t&, const md5_t&);
		bool operator != (const md5_t&, const md5_t&);

		md5_t calculate_md5(const void* data, size_t size);
	}

	namespace convert
	{
		std::wstring to_wstring(const cryptography::md5_t&);
	}
}
