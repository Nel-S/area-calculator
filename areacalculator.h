#ifndef AREA_CALCULATOR_AREACALCULATOR_H
#define AREA_CALCULATOR_AREACALCULATOR_H

#include <cinttypes>
#include <queue>

#include "src/util.h"

namespace AreaCalculator {

	// Abstract base struct for flood fill tests
	template <typename T>
	struct Tester {
		[[nodiscard]] virtual bool test(const T &x, const T &z) = 0;
		// virtual ~Tester() = 0;
	};

	// Result struct for the flood fill.
	template <typename T>
	struct Result : AreaUtilities::BoundingBox<T> {
		uint64_t area;

		constexpr Result(const T &x, const T &z) noexcept : AreaUtilities::BoundingBox<T>(x, z), area(0) {}
		constexpr Result(const T &minX, const T &maxX, const T &minZ, const T &maxZ) noexcept : AreaUtilities::BoundingBox<T>(minX, maxX, minZ, maxZ), area(0) {}

		// Adds a pixel to the area + bounding box.
		void add(const T &x, const T &z) noexcept {
			++this->area;
			AreaUtilities::BoundingBox<T>::add(x, z);
		}
	};

	/* Calculates the area and bounding box under the provided Tester and starting coordinate.
	The algorithm was largely ported from the final pseudocode in https://en.wikipedia.org/w/index.php?title=Flood_fill&oldid=1304229346#Span_filling .*/
	template <typename T>
	Result<T> calculate(Tester<T> &tester, const T &initialX, const T &initialZ) {
		// Initialize result bounding box with starting coordinate
		Result<T> result(initialX, initialZ);

		// Stop immediately if the first coordinate fails
		if (!tester.test(initialX, initialZ)) return result;

		// Tracks which (z-axis) spans have already been added to the tracker.
		std::unordered_map<T, std::forward_list<AreaUtilities::Span<T>>> visitedSpans;
		std::queue<AreaUtilities::BoundingBox<T>> queue;
		// Initial spans to begin checking
		queue.push({initialX, initialX, initialZ, 1});
		queue.push({initialX, initialX, initialZ - 1, -1});
		while (!queue.empty()) {
			// We reuse a BoundingBox to avoid defining another structure with the same setup of attributes, even though maxZ is interpreted differently
			AreaUtilities::BoundingBox currentBox = queue.front();
			const T &z = currentBox.minZ, dz = currentBox.maxZ;
			T x = currentBox.minX;

			// If the current pixel is valid, add all valid pixels immediately to its left
			if (!AreaUtilities::Span<T>::visitedSpansContains(visitedSpans, x, z) && tester.test(x, z)) {
				while (!AreaUtilities::Span<T>::visitedSpansContains(visitedSpans, x - 1, z) && tester.test(x - 1, z)) result.add(--x, z);
				/* Then mark that span on the row that was just left, in case it had been blocked by a pixel on the left.
				We don't need to add a span to the unordered map because the loop below always runs at least once.*/
				if (x < currentBox.minX) queue.push({x, currentBox.minX - 1, z - dz, -dz});
			}
			// Then, iterating to the right:
			do {
				// Add all pixels until a wall is reached
				while (!AreaUtilities::Span<T>::visitedSpansContains(visitedSpans, currentBox.minX, z) && tester.test(currentBox.minX, z)) result.add(currentBox.minX++, z);
				// If any pixels had been added this round at all (either to the left or the right), mark the full span checked for the next row
				if (x < currentBox.minX) {
					AreaUtilities::Span<T>::addSpanTo(visitedSpans[z], {x, currentBox.minX - 1});
					queue.push({x, currentBox.minX - 1, z + dz, dz});
				}
				/* If the original right border had been passed, mark the span from the old right border to the new one for the row that was just left.
				We don't need to add another span because x is guaranteed to be <= currentBox.maxX + 1.*/
				if (currentBox.minX - 1 > currentBox.maxX) queue.push({currentBox.maxX + 1, currentBox.minX - 1, z - dz, -dz});
				// Continue iterating rightwards until the wall is passed (if it was previously hit above) or the old right border is reached
				do {++currentBox.minX;} while (currentBox.minX < currentBox.maxX && (AreaUtilities::Span<T>::visitedSpansContains(visitedSpans, currentBox.minX, z) || !tester.test(currentBox.minX, z)));
				x = currentBox.minX;
			} while (currentBox.minX <= currentBox.maxX);
			queue.pop();
		}
		return result;
	}
}

#endif