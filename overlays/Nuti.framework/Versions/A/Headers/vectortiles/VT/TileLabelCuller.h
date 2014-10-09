#pragma once

#include "TileLabel.h"

#include <array>
#include <vector>
#include <list>
#include <unordered_map>
#include <memory>
#include <mutex>

#include <cglib/vec.h>
#include <cglib/mat.h>
#include <cglib/bbox.h>

namespace Nuti {
	namespace VT {
		class TileLabelCuller {
		public:
			TileLabelCuller(std::mutex& mutex, float scale);
			virtual ~TileLabelCuller() = default;

			void setViewState(const cglib::mat4x4<double>& projectionMatrix, const cglib::mat4x4<double>& cameraMatrix, float zoom, float aspectRatio);
			void process(const std::vector<std::shared_ptr<TileLabel>>& labelList);

		private:
			enum { RESOLUTION = 16 };

			struct Record {
				cglib::bounding_box<float, 2> bounds;
				std::array<cglib::vec2<float>, 4> envelope;
				std::shared_ptr<TileLabel> label;
			};

			void clearGrid();
			bool testOverlap(const std::shared_ptr<TileLabel>& label);

			static int getGridIndex(float x);
			static cglib::mat4x4<double> calculateLocalViewMatrix(const cglib::mat4x4<double>& cameraMatrix);

			cglib::mat4x4<float> _mvpMatrix;
			TileLabel::ViewState _labelViewState;
			std::vector<Record> _recordGrid[RESOLUTION][RESOLUTION];

			const float _scale;
			std::mutex& _mutex;
		};
	}
}
