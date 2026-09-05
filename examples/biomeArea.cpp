#include "../areacalculator.h"

#include <algorithm>
#include <cstdint>
#include <string.h>

#include "cubiomes/biomes.h"
#include "cubiomes/generator.h"
#include "cubiomes/util.h"

namespace MinecraftStringUtilities {
	// Attempts to decipher a string as a Minecraft biome.
	[[nodiscard]] int32_t interpretAsBiome(const char *const string) {
		std::string lowercaseString = StringUtilities::toLowercase(string);
		std::replace(lowercaseString.begin(), lowercaseString.end(), '_', ' ');
		if (lowercaseString == "none" || lowercaseString == "na" || lowercaseString == "null" || lowercaseString == "0") return none;
		if (lowercaseString == "ocean") return ocean;
		if (lowercaseString == "plains") return plains;
		if (lowercaseString == "desert") return desert;
		if (lowercaseString == "mountains" || lowercaseString == "extreme hills" || lowercaseString == "windswept hills") return mountains;
		if (lowercaseString == "forest") return forest;
		if (lowercaseString == "taiga") return taiga;
		if (lowercaseString == "swamp" || lowercaseString == "swampland") return swamp;
		if (lowercaseString == "river") return river;
		if (lowercaseString == "nether wastes" || lowercaseString == "nether") return nether_wastes;
		if (lowercaseString == "the end" || lowercaseString == "end" || lowercaseString == "sky") return the_end;
		if (lowercaseString == "frozen ocean" || lowercaseString == "frozen ocean") return frozen_ocean;
		if (lowercaseString == "frozen river" || lowercaseString == "frozen river") return frozen_river;
		if (lowercaseString == "snowy tundra" || lowercaseString == "ice plains" || lowercaseString == "snowy plains") return snowy_tundra;
		if (lowercaseString == "snowy mountains" || lowercaseString == "ice mountains") return snowy_mountains;
		if (lowercaseString == "mushroom fields" || lowercaseString == "mushroom island") return mushroom_fields;
		if (lowercaseString == "mushroom field shore" || lowercaseString == "mushroom island shore") return mushroom_field_shore;
		if (lowercaseString == "beach") return beach;
		if (lowercaseString == "desert hills" || lowercaseString == "desert hills") return desert_hills;
		if (lowercaseString == "wooded hills" || lowercaseString == "forest hills") return wooded_hills;
		if (lowercaseString == "taiga hills" || lowercaseString == "taiga hills") return taiga_hills;
		if (lowercaseString == "mountain edge" || lowercaseString == "extreme hills edge") return mountain_edge;
		if (lowercaseString == "jungle") return jungle;
		if (lowercaseString == "jungle hills" || lowercaseString == "jungle hills") return jungle_hills;
		if (lowercaseString == "jungle edge" || lowercaseString == "jungle edge" || lowercaseString == "sparse jungle") return jungle_edge;
		if (lowercaseString == "deep ocean" || lowercaseString == "deep ocean") return deep_ocean;
		if (lowercaseString == "stone shore" || lowercaseString == "stone beach" || lowercaseString == "stony shore") return stone_shore;
		if (lowercaseString == "snowy beach" || lowercaseString == "cold beach") return snowy_beach;
		if (lowercaseString == "birch forest" || lowercaseString == "birch forest") return birch_forest;
		if (lowercaseString == "birch forest hills" || lowercaseString == "birch forest hills") return birch_forest_hills;
		if (lowercaseString == "dark forest" || lowercaseString == "roofed forest") return dark_forest;
		if (lowercaseString == "snowy taiga" || lowercaseString == "cold taiga") return snowy_taiga;
		if (lowercaseString == "snowy taiga hills" || lowercaseString == "cold taiga hills") return snowy_taiga_hills;
		if (lowercaseString == "giant tree taiga" || lowercaseString == "mega taiga" || lowercaseString == "old growth pine taiga") return giant_tree_taiga;
		if (lowercaseString == "giant tree taiga hills" || lowercaseString == "mega taiga hills") return giant_tree_taiga_hills;
		if (lowercaseString == "wooded mountains" || lowercaseString == "extreme hills plus" || lowercaseString == "windswept forest") return wooded_mountains;
		if (lowercaseString == "savanna") return savanna;
		if (lowercaseString == "savanna plateau" || lowercaseString == "savanna plateau") return savanna_plateau;
		if (lowercaseString == "badlands" || lowercaseString == "mesa") return badlands;
		if (lowercaseString == "wooded badlands plateau" || lowercaseString == "mesa plateau f" || lowercaseString == "wooded badlands") return wooded_badlands_plateau;
		if (lowercaseString == "badlands plateau" || lowercaseString == "mesa plateau") return badlands_plateau;
		if (lowercaseString == "small end islands") return small_end_islands;
		if (lowercaseString == "end midlands") return end_midlands;
		if (lowercaseString == "end highlands") return end_highlands;
		if (lowercaseString == "end barrens") return end_barrens;
		if (lowercaseString == "warm ocean" || lowercaseString == "warm ocean") return warm_ocean;
		if (lowercaseString == "lukewarm ocean" || lowercaseString == "lukewarm ocean") return lukewarm_ocean;
		if (lowercaseString == "cold ocean" || lowercaseString == "cold ocean") return cold_ocean;
		if (lowercaseString == "deep warm ocean" || lowercaseString == "warm deep ocean") return deep_warm_ocean;
		if (lowercaseString == "deep lukewarm ocean" || lowercaseString == "lukewarm deep ocean") return deep_lukewarm_ocean;
		if (lowercaseString == "deep cold ocean" || lowercaseString == "cold deep ocean") return deep_cold_ocean;
		if (lowercaseString == "deep frozen ocean" || lowercaseString == "frozen deep ocean") return deep_frozen_ocean;
		if (lowercaseString == "seasonal forest") return seasonal_forest;
		if (lowercaseString == "rainforest") return rainforest;
		if (lowercaseString == "shrubland") return shrubland;
		if (lowercaseString == "the void" || lowercaseString == "void") return the_void;
		if (lowercaseString == "sunflower plains") return sunflower_plains;
		if (lowercaseString == "desert lakes") return desert_lakes;
		if (lowercaseString == "gravelly mountains" || lowercaseString == "windswept gravelly hills") return gravelly_mountains;
		if (lowercaseString == "flower forest") return flower_forest;
		if (lowercaseString == "taiga mountains") return taiga_mountains;
		if (lowercaseString == "swamp hills") return swamp_hills;
		if (lowercaseString == "ice spikes") return ice_spikes;
		if (lowercaseString == "modified jungle") return modified_jungle;
		if (lowercaseString == "modified jungle edge") return modified_jungle_edge;
		if (lowercaseString == "tall birch forest" || lowercaseString == "old growth birch forest") return tall_birch_forest;
		if (lowercaseString == "tall birch hills") return tall_birch_hills;
		if (lowercaseString == "dark forest hills") return dark_forest_hills;
		if (lowercaseString == "snowy taiga mountains") return snowy_taiga_mountains;
		if (lowercaseString == "giant spruce taiga" || lowercaseString == "old growth spruce taiga") return giant_spruce_taiga;
		if (lowercaseString == "giant spruce taiga hills") return giant_spruce_taiga_hills;
		if (lowercaseString == "modified gravelly mountains") return modified_gravelly_mountains;
		if (lowercaseString == "shattered savanna" || lowercaseString == "windswept savanna") return shattered_savanna;
		if (lowercaseString == "shattered savanna plateau") return shattered_savanna_plateau;
		if (lowercaseString == "eroded badlands") return eroded_badlands;
		if (lowercaseString == "modified wooded badlands plateau") return modified_wooded_badlands_plateau;
		if (lowercaseString == "modified badlands plateau") return modified_badlands_plateau;
		if (lowercaseString == "bamboo jungle") return bamboo_jungle;
		if (lowercaseString == "bamboo jungle hills") return bamboo_jungle_hills;
		if (lowercaseString == "soul sand valley") return soul_sand_valley;
		if (lowercaseString == "crimson forest") return crimson_forest;
		if (lowercaseString == "warped forest") return warped_forest;
		if (lowercaseString == "basalt deltas") return basalt_deltas;
		if (lowercaseString == "dripstone caves") return dripstone_caves;
		if (lowercaseString == "lush caves") return lush_caves;
		if (lowercaseString == "meadow") return meadow;
		if (lowercaseString == "grove") return grove;
		if (lowercaseString == "snowy slopes") return snowy_slopes;
		if (lowercaseString == "jagged peaks") return jagged_peaks;
		if (lowercaseString == "frozen peaks") return frozen_peaks;
		if (lowercaseString == "stony peaks") return stony_peaks;
		if (lowercaseString == "deep dark") return deep_dark;
		if (lowercaseString == "mangrove swamp") return mangrove_swamp;
		if (lowercaseString == "cherry grove") return cherry_grove;
		if (lowercaseString == "pale garden") return pale_garden;
		throw std::runtime_error("Could not interpret \"" + lowercaseString + "\" as a Minecraft biome.");
	}

	// Attempts to decipher a string as a Minecraft dimension.
	[[nodiscard]] int32_t interpretAsDimension(const char *const string) {
		std::string lowercaseString = StringUtilities::toLowercase(string);
		std::replace(lowercaseString.begin(), lowercaseString.end(), '_', ' ');
		if (
			lowercaseString == "o" || lowercaseString == "ow" || lowercaseString == "overworld"
			|| lowercaseString == "the overworld"
		) return DIM_OVERWORLD;
		if (
			lowercaseString == "n" || lowercaseString == "nether"
			|| lowercaseString == "the nether"
		) return DIM_NETHER;
		if (
			lowercaseString == "e" || lowercaseString == "end"
			|| lowercaseString == "the end"
		) return DIM_END;
		throw std::runtime_error("Could not interpret \"" + lowercaseString + "\" as a Minecraft dimension.");
	}

	// Attempts to decipher a string as a Minecraft dimension.
	[[nodiscard]] const char *dimensionToString(int32_t dimension) {
		switch (dimension) {
			case DIM_OVERWORLD: return "the Overworld";
			case DIM_NETHER: return "the Nether";
			case DIM_END: return "the End";
		}
		return "[Invalid Minecraft dimension]";
	}
}

/* Example test function.
   Returns whether the current coordinate is a mushroom fields biome.
*/
struct BiomeTester : public AreaCalculator::Tester<int32_t> {
	Generator generator;
	int32_t biome, y;
	int *biomeStorage;

	BiomeTester(int32_t version, uint64_t worldseed, int32_t dimension, int32_t initialX, int32_t y, int32_t initialZ, bool largeBiomes, int32_t biome) noexcept {
		this->y = y;
		this->biome = biome;
		if (dimension == DIM_UNDEF) dimension = getDimension(biome);

		setupGenerator(&this->generator, version, largeBiomes);
		applySeed(&this->generator, dimension, worldseed);

		// Pre-allocate biome storage so we don't need to allocate/free memory every time test() is called
		this->biomeStorage = allocCache(&this->generator, {1, initialX, initialZ, 1, 1, y, 1});
	}

	~BiomeTester() noexcept {
		free(this->biomeStorage);
	}

	[[nodiscard]] bool test(const int32_t &x, const int32_t &z) override {
		if (genBiomes(&this->generator, this->biomeStorage, {1, x, z, 1, 1, this->y, 1})) return false;
		if (this->biome == none) {
			this->biome = this->biomeStorage[0];
			return true;
		}
		return this->biomeStorage[0] == this->biome;
	}

};

int main(int argc, char **argv) {
	// Default arguments
	uint64_t worldseed = 0, maxIterations = UINT64_MAX;
	int32_t version = MC_NEWEST, dimension = DIM_UNDEF, initialX = 0, y = 0, initialZ = 0, biome = none;
	bool largeBiomes = false;

	// Get arguments from user
	for (int i = 1; i < argc - 1; ++i) {
		if (!argv[i] || argv[i][0] != '-' || argv[i][1] != '-') continue; // We use 2 dashes to avoid potentially-misinterpreted negative numbers
		std::string argument = StringUtilities::toLowercase(argv[i]);
		if (argument == "--version") version = str2mc(argv[++i]);
		else if (argument == "--seed" || argument == "--worldseed") worldseed = std::strtoll(argv[++i], NULL, 10);
		else if (argument == "--dimension") dimension = MinecraftStringUtilities::interpretAsDimension(argv[++i]);
		else if (argument == "--x") initialX = std::strtol(argv[++i], NULL, 10);
		else if (argument == "--y") y = std::strtol(argv[++i], NULL, 10);
		else if (argument == "--z") initialZ = std::strtol(argv[++i], NULL, 10);
		else if (argument == "--largebiomes") largeBiomes = StringUtilities::interpretAsBoolean(argv[++i]);
		else if (argument == "--biome") biome = MinecraftStringUtilities::interpretAsBiome(argv[++i]);
		else if (argument == "--maxiterations") maxIterations = std::strtoull(argv[++i], NULL, 10);
	}
	
	// Run flood fill and print final area + bounding boxes
	BiomeTester tester(version, worldseed, dimension, initialX, y, initialZ, largeBiomes, biome);
	AreaCalculator::Result<int32_t> result = AreaCalculator::calculate(tester, initialX, initialZ, maxIterations);

	if (!result.area) {
		if (biome == none) {
			std::printf(
			"%sNo biome could be determined at (%" PRId32 ", %" PRId32 ") in %s on seed %" PRId64 " on version %s%s.",
			result.haltedEarly ? "[Halted early]\n" : "",
			initialX, initialZ, MinecraftStringUtilities::dimensionToString(tester.generator.dim), worldseed, mc2str(version), largeBiomes ? " under Large Biomes generation" : ""
		);
		} else {
			std::printf(
				"%sA %s biome does not exist at (%" PRId32 ", %" PRId32 ") in %s on seed %" PRId64 " on version %s%s.",
				result.haltedEarly ? "[Halted early]\n" : "",
				biome2str(version, biome),
				initialX, initialZ, MinecraftStringUtilities::dimensionToString(tester.generator.dim), worldseed, mc2str(version), largeBiomes ? " under Large Biomes generation" : ""
			);
		}
		return 1;
	}

	uint64_t xRange = static_cast<int64_t>(result.maxX) - result.minX + 1;
	uint64_t zRange = static_cast<int64_t>(result.maxZ) - result.minZ + 1;
	std::printf(
		"%sBiome:   %s\nArea:    %" PRIu64 " square block%s\nX-range: [%" PRId32 ", %" PRId32 "] = %" PRIu64 " block%s\nZ-range: [%" PRId32 ", %" PRId32 "] = %" PRIu64 " block%s\n",
		result.haltedEarly ? "[Halted early]\n" : "",
		biome2str(tester.generator.mc, tester.biome),
		result.area, result.area != 1 ? "s" : "",
		result.minX, result.maxX, xRange, xRange != 1 ? "s" : "",
		result.minZ, result.maxZ, zRange, zRange != 1 ? "s" : ""
	);
	return 0;
}