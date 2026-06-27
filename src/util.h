#ifndef AREA_CALCULATOR_UTIL_H
#define AREA_CALCULATOR_UTIL_H

#include <algorithm>
#include <forward_list>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace AreaUtilities {

	// A one-dimensional contiguous span.
	template <typename T> struct Span {
		T left, right;

		constexpr Span(const T &left = 0, const T &right = 0) noexcept : left(std::min(left, right)), right(std::max(left, right)) {}

		// Returns if the span contains the provided value.
		[[nodiscard]] constexpr bool contains(const T &value) const noexcept {
			return this->left <= value && value <= this->right;
		}

		// Attempts to absorb the provided span into the original one. Returns whether it succeeded.
		constexpr bool expand(const Span<T> &other) noexcept {
			if (this->right + 1 < other.left || other.right + 1 < this->left) return false;
			this->left = std::min(this->left, other.left);
			this->right = std::max(this->right, other.right);
			return true;
		}

		// Adds a new span to the map's corresponding forward_list, having it be absorbed if possible or appending it otherwise.
		static void addSpanTo(std::forward_list<Span<T>> &forward_list, const Span<T> &span) noexcept {
			for (Span<T> &oldSpan : forward_list) {
				if (oldSpan.expand(span)) return;
			}
			forward_list.push_front(span);
		}

		[[nodiscard]] static bool visitedSpansContains(const std::unordered_map<T, std::forward_list<Span<T>>> &visitedSpans, const T &x, const T &z) {
		auto visitedSpan = visitedSpans.find(z);
		if (visitedSpan == visitedSpans.end()) return false;

		for (const Span<T> &span : visitedSpan->second) {
			if (span.contains(x)) return true;
		}
		return false;
	}
	};

	// A two-dimensional bounding box.
	template <typename T> struct BoundingBox {
		T minX, maxX, minZ, maxZ;

		constexpr BoundingBox(const T& x = 0, const T& z = 0) noexcept : minX(x), maxX(x), minZ(z), maxZ(z) {}
		constexpr BoundingBox(const T& minX, const T& maxX, const T& minZ, const T& maxZ) noexcept : minX(minX), maxX(maxX), minZ(minZ), maxZ(maxZ) {}

		// Expands the bounding box to encompass the provided coordinate.
		constexpr void add(const T& x, const T& z) noexcept {
			if (x < this->minX) this->minX = x;
			if (x > this->maxX) this->maxX = x;
			if (z < this->minZ) this->minZ = z;
			if (z > this->maxZ) this->maxZ = z;
		}
	};
}

namespace StringUtilities {
	// Converts a string to lowercase.
	// [[nodiscard]] static std::string toLowercase(std::string &string) noexcept {
	// 	std::transform(string.begin(), string.end(), string.begin(), [](unsigned char character){return std::tolower(character);});
	// 	return string;
	// }

	// Converts a C-string to lowercase.
	[[nodiscard]] static std::string toLowercase(const char *string) noexcept {
		std::string newString = string ? std::string(string) : "";
		std::transform(newString.begin(), newString.end(), newString.begin(), [](unsigned char character){return std::tolower(character);});
		return newString;
	}

	// Attempts to decipher a string as a Boolean value.
	[[nodiscard]] static bool interpretAsBoolean(const char *const string) {
		std::string lowercaseString = toLowercase(string);
		if (lowercaseString == "t" || lowercaseString == "y" || lowercaseString == "true" || lowercaseString == "yes" || lowercaseString == "1") return true;
		if (lowercaseString == "f" || lowercaseString == "n" || lowercaseString == "false" || lowercaseString == "no" || lowercaseString == "0") return false;
		throw std::runtime_error("Could not interpret \"" + lowercaseString + "\" as a Boolean.");
	}
}

#endif