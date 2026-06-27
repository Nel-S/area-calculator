#include "../areacalculator.h"
#include "cubiomes/generator.h"

/* Example test function.
   Returns whether the current coordinate is a mushroom fields biome.
*/
struct MushroomIslandTester : public AreaCalculator::Tester<int32_t> {
    Generator g;
    int *biomeStorage;

    static constexpr int32_t SEA_LEVEL = 62;

    MushroomIslandTester(uint64_t worldseed, int32_t initialX, int32_t initialZ, bool largeBiomes) noexcept {
	    setupGenerator(&this->g, MC_NEWEST, largeBiomes);
	    applySeed(&this->g, DIM_OVERWORLD, worldseed);

        // Pre-allocate biome storage so we don't need to allocate/free memory every time test() is called
	    this->biomeStorage = allocCache(&g, {1, initialX, initialZ, 1, 1, SEA_LEVEL, 1});
    }

    ~MushroomIslandTester() noexcept {
        free(this->biomeStorage);
    }

    [[nodiscard]] bool test(const int32_t &x, const int32_t &z) override {
        /* There's a potential optimization possible if coordinates are made to represent 4x4 blocks, since climates are largely sampled on a 1:4 scale.
           However this has not been pursued yet.*/
        return !genBiomeNoiseScaled(&this->g.bn, this->biomeStorage, {1, x, z, 1, 1, SEA_LEVEL, 1}, g.sha) && this->biomeStorage[0] == mushroom_fields;
    }

};

int main(int argc, char **argv) {
	// Default arguments
	uint64_t worldseed = 0;
	int32_t initialX = 0, initialZ = 0;
	bool largeBiomes = false;

	// Get arguments from user
	for (int i = 1; i < argc - 1; ++i) {
		if (!argv[i] || argv[i][0] != '-' || argv[i][1] != '-') continue; // We use 2 dashes to avoid potentially-misinterpreted negative numbers
		std::string argument = StringUtilities::toLowercase(argv[i]);
		if (argument == "--worldseed") worldseed = std::strtoll(argv[++i], NULL, 10);
		else if (argument == "--x") initialX = std::strtol(argv[++i], NULL, 10);
		else if (argument == "--z") initialZ = std::strtol(argv[++i], NULL, 10);
		else if (argument == "--largebiomes") largeBiomes = StringUtilities::interpretAsBoolean(argv[++i]);
	}
	
	// Run flood fill and print final area + bounding boxes
	MushroomIslandTester tester(worldseed, initialX, initialZ, largeBiomes);
	AreaCalculator::Result<int32_t> result = AreaCalculator::calculate(tester, initialX, initialZ);
	if (!result.area) {
		std::printf(
			"A mushroom island does not exist at (%" PRId32 ", %" PRId32 ") on seed %" PRId64 "%s.",
			initialX, initialZ, worldseed, largeBiomes ? " under Large Biomes generation" : ""
		);
	}
	else {
		std::printf(
			"Area:    %" PRIu64 " square blocks\nX-range: [%" PRId32 ", %" PRId32 "] = %" PRIu64 " blocks\nZ-range: [%" PRId32 ", %" PRId32 "] = %" PRIu64 " blocks\n",
			result.area,
			result.minX, result.maxX, static_cast<int64_t>(result.maxX) - result.minX + 1,
			result.minZ, result.maxZ, static_cast<int64_t>(result.maxZ) - result.minZ + 1
		);
	}
	return 0;
}