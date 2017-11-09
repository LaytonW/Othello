#include <limits>

#include "utils.hpp"
#include "othello.hpp"

using namespace Othello;

using OthelloRow =
  BitType<isqrt<std::numeric_limits<OthelloBitBoard>::digits>::value>;

constexpr auto othelloRowSize = std::numeric_limits<OthelloRow>::digits;

constexpr std::size_t indexOf(const OthelloPlayer player) {
  return player == black ? 0 : 1;
}

OthelloGame::OthelloGame() {
  this->blackBitBoard |= positionToBoard<OthelloBitBoard>(3, 4);
  this->blackBitBoard |= positionToBoard<OthelloBitBoard>(4, 3);
  this->whiteBitBoard |= positionToBoard<OthelloBitBoard>(3, 3);
  this->whiteBitBoard |= positionToBoard<OthelloBitBoard>(4, 4);
}

const OthelloState OthelloGame::getState(void) const {
  return std::make_tuple(this->blackBitBoard, this->whiteBitBoard);
}

const OthelloMoves OthelloGame::getMoves(const OthelloState& state,
                                         const OthelloPlayer player) const {
  OthelloBitBoard moves = 0;

  const OthelloBitBoard playerBoard =
    player == black ? std::get<indexOf(black)>(state)
                    : std::get<indexOf(white)>(state);

  const OthelloBitBoard opponentBoard =
    player == black ? std::get<indexOf(white)>(state)
                    : std::get<indexOf(black)>(state);

  OthelloBitBoard rotate0Moves = 0;

  for (std::size_t i = 0; i < othelloRowSize; i++) {
    const OthelloRow playerRow   = getRow(playerBoard, i);
    const OthelloRow opponentRow = getRow(opponentBoard, i);

    const OthelloRow playerLast = extractLastOne(playerRow);
    const OthelloRow playerNext = playerLast >> 1;

    const OthelloRow move = playerNext & opponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(fillTail(playerNext) ^ opponentRow)
      ) : 0;

    rotate0Moves <<= othelloRowSize;
    rotate0Moves |= move;
  }

  moves |= rotate0Moves;

  const auto clockRotate45PlayerBoard   = clockRotate45(playerBoard);
  const auto clockRotate45OpponentBoard = clockRotate45(opponentBoard);

  OthelloBitBoard clockRotate45Moves = 0;

  for (std::size_t i = 0; i < othelloRowSize; i++) {
    const OthelloRow playerRow   = getRow(clockRotate45PlayerBoard, i);
    const OthelloRow opponentRow = getRow(clockRotate45OpponentBoard, i);

    if (i == othelloRowSize - 1) { // Diagonal row
      const OthelloRow playerLast = extractLastOne(playerRow);
      const OthelloRow playerNext = playerLast >> 1;

      const OthelloRow move = playerNext & opponentRow
        ? extractFirstOne(
          static_cast<OthelloRow>(fillTail(playerNext) ^ opponentRow)
        ) : 0;

      clockRotate45Moves <<= othelloRowSize;
      clockRotate45Moves |= move;

      continue;
    }

    const OthelloRow lowerMask = fillTail(
      static_cast<OthelloRow>(1 << (othelloRowSize - 2 - i))
    );
    const OthelloRow upperMask = ~lowerMask;

    const OthelloRow upperPlayerRow   = playerRow & upperMask;
    const OthelloRow upperOpponentRow = opponentRow & upperMask;

    const OthelloRow lowerPlayerRow   = playerRow & lowerMask;
    const OthelloRow lowerOpponentRow = opponentRow & lowerMask;

    const OthelloRow upperPlayerLast = extractLastOne(upperPlayerRow);
    const OthelloRow upperPlayerNext = upperPlayerLast >> 1;

    const OthelloRow lowerPlayerLast = extractLastOne(lowerPlayerRow);
    const OthelloRow lowerPlayerNext = lowerPlayerLast >> 1;

    const OthelloRow upperMove = upperPlayerNext & upperOpponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(fillTail(upperPlayerNext) ^ upperOpponentRow)
      ) & upperMask : 0;

    const OthelloRow lowerMove = lowerPlayerNext & lowerOpponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(fillTail(lowerPlayerNext) ^ lowerOpponentRow)
      ) & lowerMask : 0;

    clockRotate45Moves <<= othelloRowSize;
    clockRotate45Moves |= (upperMove | lowerMove);
  }

  moves |= antiClockRotate45(clockRotate45Moves);

  const auto clockRotate90PlayerBoard   = clockRotate90(playerBoard);
  const auto clockRotate90OpponentBoard = clockRotate90(opponentBoard);

  OthelloBitBoard clockRotate90Moves = 0;

  for (std::size_t i = 0; i < othelloRowSize; i++) {
    const OthelloRow playerRow   = getRow(clockRotate90PlayerBoard, i);
    const OthelloRow opponentRow = getRow(clockRotate90OpponentBoard, i);

    const OthelloRow playerLast = extractLastOne(playerRow);
    const OthelloRow playerNext = playerLast >> 1;

    const OthelloRow move = playerNext & opponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(fillTail(playerNext) ^ opponentRow)
      ) : 0;

    clockRotate90Moves <<= othelloRowSize;
    clockRotate90Moves |= move;
  }

  moves |= antiClockRotate90(clockRotate90Moves);

  const auto clockRotate135PlayerBoard   =
    clockRotate45(clockRotate90PlayerBoard);
  const auto clockRotate135OpponentBoard =
    clockRotate45(clockRotate90OpponentBoard);

  OthelloBitBoard clockRotate135Moves = 0;

  for (std::size_t i = 0; i < othelloRowSize; i++) {
    const OthelloRow playerRow   = getRow(clockRotate135PlayerBoard, i);
    const OthelloRow opponentRow = getRow(clockRotate135OpponentBoard, i);

    if (i == othelloRowSize - 1) { // Diagonal row
      const OthelloRow playerLast = extractLastOne(playerRow);
      const OthelloRow playerNext = playerLast >> 1;

      const OthelloRow move = playerNext & opponentRow
        ? extractFirstOne(
          static_cast<OthelloRow>(fillTail(playerNext) ^ opponentRow)
        ) : 0;

      clockRotate135Moves <<= othelloRowSize;
      clockRotate135Moves |= move;

      continue;
    }

    const OthelloRow lowerMask = fillTail(
      static_cast<OthelloRow>(1 << (othelloRowSize - 2 - i))
    );
    const OthelloRow upperMask = ~lowerMask;

    const OthelloRow upperPlayerRow   = playerRow & upperMask;
    const OthelloRow upperOpponentRow = opponentRow & upperMask;

    const OthelloRow lowerPlayerRow   = playerRow & lowerMask;
    const OthelloRow lowerOpponentRow = opponentRow & lowerMask;

    const OthelloRow upperPlayerLast = extractLastOne(upperPlayerRow);
    const OthelloRow upperPlayerNext = upperPlayerLast >> 1;

    const OthelloRow lowerPlayerLast = extractLastOne(lowerPlayerRow);
    const OthelloRow lowerPlayerNext = lowerPlayerLast >> 1;

    const OthelloRow upperMove = upperPlayerNext & upperOpponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(fillTail(upperPlayerNext) ^ upperOpponentRow)
      ) & upperMask : 0;

    const OthelloRow lowerMove = lowerPlayerNext & lowerOpponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(fillTail(lowerPlayerNext) ^ lowerOpponentRow)
      ) & lowerMask : 0;

    clockRotate135Moves <<= othelloRowSize;
    clockRotate135Moves |= (upperMove | lowerMove);
  }

  moves |= antiClockRotate90(antiClockRotate45(clockRotate135Moves));

  const auto rotate180PlayerBoard   = rotate180(playerBoard);
  const auto rotate180OpponentBoard = rotate180(opponentBoard);

  OthelloBitBoard rotate180Moves = 0;

  for (std::size_t i = 0; i < othelloRowSize; i++) {
    const OthelloRow playerRow   = getRow(rotate180PlayerBoard, i);
    const OthelloRow opponentRow = getRow(rotate180OpponentBoard, i);

    const OthelloRow playerLast = extractLastOne(playerRow);
    const OthelloRow playerNext = playerLast >> 1;

    const OthelloRow move = playerNext & opponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(fillTail(playerNext) ^ opponentRow)
      ) : 0;

    rotate180Moves <<= othelloRowSize;
    rotate180Moves |= move;
  }

  moves |= rotate180(rotate180Moves);

  const auto antiClockRotate45PlayerBoard   = antiClockRotate45(playerBoard);
  const auto antiClockRotate45OpponentBoard = antiClockRotate45(opponentBoard);

  OthelloBitBoard antiClockRotate45Moves = 0;

  for (std::size_t i = 0; i < othelloRowSize; i++) {
    const OthelloRow playerRow   = getRow(antiClockRotate45PlayerBoard, i);
    const OthelloRow opponentRow = getRow(antiClockRotate45OpponentBoard, i);

    if (i == 0) { // Diagonal row
      const OthelloRow playerLast = extractLastOne(playerRow);
      const OthelloRow playerNext = playerLast >> 1;

      const OthelloRow move = playerNext & opponentRow
        ? extractFirstOne(
          static_cast<OthelloRow>(fillTail(playerNext) ^ opponentRow)
        ) : 0;

      antiClockRotate45Moves <<= othelloRowSize;
      antiClockRotate45Moves |= move;

      continue;
    }

    const OthelloRow lowerMask = fillTail(
      static_cast<OthelloRow>(1 << (i - 1))
    );
    const OthelloRow upperMask = ~lowerMask;

    const OthelloRow upperPlayerRow   = playerRow & upperMask;
    const OthelloRow upperOpponentRow = opponentRow & upperMask;

    const OthelloRow lowerPlayerRow   = playerRow & lowerMask;
    const OthelloRow lowerOpponentRow = opponentRow & lowerMask;

    const OthelloRow upperPlayerLast = extractLastOne(upperPlayerRow);
    const OthelloRow upperPlayerNext = upperPlayerLast >> 1;

    const OthelloRow lowerPlayerLast = extractLastOne(lowerPlayerRow);
    const OthelloRow lowerPlayerNext = lowerPlayerLast >> 1;

    const OthelloRow upperMove = upperPlayerNext & upperOpponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(fillTail(upperPlayerNext) ^ upperOpponentRow)
      ) & upperMask : 0;

    const OthelloRow lowerMove = lowerPlayerNext & lowerOpponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(fillTail(lowerPlayerNext) ^ lowerOpponentRow)
      ) & lowerMask : 0;

    antiClockRotate45Moves <<= othelloRowSize;
    antiClockRotate45Moves |= (upperMove | lowerMove);
  }

  moves |= clockRotate45(antiClockRotate45Moves);

  const auto antiClockRotate90PlayerBoard   = antiClockRotate90(playerBoard);
  const auto antiClockRotate90OpponentBoard = antiClockRotate90(opponentBoard);

  OthelloBitBoard antiClockRotate90Moves = 0;

  for (std::size_t i = 0; i < othelloRowSize; i++) {
    const OthelloRow playerRow   = getRow(antiClockRotate90PlayerBoard, i);
    const OthelloRow opponentRow = getRow(antiClockRotate90OpponentBoard, i);

    const OthelloRow playerLast = extractLastOne(playerRow);
    const OthelloRow playerNext = playerLast >> 1;

    const OthelloRow move = playerNext & opponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(fillTail(playerNext) ^ opponentRow)
      ) : 0;

    antiClockRotate90Moves <<= othelloRowSize;
    antiClockRotate90Moves |= move;
  }

  moves |= clockRotate90(antiClockRotate90Moves);

  const auto antiClockRotate135PlayerBoard   =
    antiClockRotate45(antiClockRotate90PlayerBoard);
  const auto antiClockRotate135OpponentBoard =
    antiClockRotate45(antiClockRotate90OpponentBoard);

  OthelloBitBoard antiClockRotate135Moves = 0;

  for (std::size_t i = 0; i < othelloRowSize; i++) {
    const OthelloRow playerRow   = getRow(antiClockRotate135PlayerBoard, i);
    const OthelloRow opponentRow = getRow(antiClockRotate135OpponentBoard, i);

    if (i == 0) { // Diagonal row
      const OthelloRow playerLast = extractLastOne(playerRow);
      const OthelloRow playerNext = playerLast >> 1;

      const OthelloRow move = playerNext & opponentRow
        ? extractFirstOne(
          static_cast<OthelloRow>(fillTail(playerNext) ^ opponentRow)
        ) : 0;

      antiClockRotate135Moves <<= othelloRowSize;
      antiClockRotate135Moves |= move;

      continue;
    }

    const OthelloRow lowerMask = fillTail(
      static_cast<OthelloRow>(1 << (i - 1))
    );
    const OthelloRow upperMask = ~lowerMask;

    const OthelloRow upperPlayerRow   = playerRow & upperMask;
    const OthelloRow upperOpponentRow = opponentRow & upperMask;

    const OthelloRow lowerPlayerRow   = playerRow & lowerMask;
    const OthelloRow lowerOpponentRow = opponentRow & lowerMask;

    const OthelloRow upperPlayerLast = extractLastOne(upperPlayerRow);
    const OthelloRow upperPlayerNext = upperPlayerLast >> 1;

    const OthelloRow lowerPlayerLast = extractLastOne(lowerPlayerRow);
    const OthelloRow lowerPlayerNext = lowerPlayerLast >> 1;

    const OthelloRow upperMove = upperPlayerNext & upperOpponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(fillTail(upperPlayerNext) ^ upperOpponentRow)
      ) & upperMask : 0;

    const OthelloRow lowerMove = lowerPlayerNext & lowerOpponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(fillTail(lowerPlayerNext) ^ lowerOpponentRow)
      ) & lowerMask : 0;

    antiClockRotate135Moves <<= othelloRowSize;
    antiClockRotate135Moves |= (upperMove | lowerMove);
  }

  moves |= clockRotate90(clockRotate45(antiClockRotate135Moves));

  return moves;
}

const OthelloState OthelloGame::getResult(const OthelloState& state,
                                          const OthelloPlayer player,
                                          const OthelloMoves  moves) const {
  auto blackBitBoard = std::get<indexOf(black)>(state);
  auto whiteBitBoard = std::get<indexOf(white)>(state);
  if (player == black)
    blackBitBoard |= moves;
  else
    whiteBitBoard |= moves;
  return std::make_tuple(blackBitBoard, whiteBitBoard);
}

void OthelloGame::applyMove(const OthelloState& state,
                            const OthelloMoves  move) {
  this->blackBitBoard = std::get<indexOf(black)>(state);
  this->whiteBitBoard = std::get<indexOf(white)>(state);
  // TODO: flip opponent tokens
  if (this->currentPlayer == black)
    blackBitBoard |= move;
  else
    whiteBitBoard |= move;
  this->currentPlayer = static_cast<OthelloPlayer>(-this->currentPlayer);
}

const OthelloUtility
OthelloGame::getUtility(const OthelloState& state,
                        const OthelloPlayer player) const {
  // TODO: check if is terminal state
  char whiteUtility =
    countOnes(this->blackBitBoard) == countOnes(this->whiteBitBoard) ? 0 :
    countOnes(this->blackBitBoard) <  countOnes(this->whiteBitBoard) ? 1 : -1;
  return player * whiteUtility;
}

const bool OthelloGame::isTerminal(const OthelloState& state) const {
  bool filled = (this->blackBitBoard | this->whiteBitBoard) ==
    ~static_cast<OthelloBitBoard>(0);
  bool noMove = this->getMoves(state, black) == 0 and
                this->getMoves(state, white) == 0;
  return filled or noMove;
}

const OthelloPlayer OthelloGame::getPlayer(void) const {
  return this->currentPlayer;
}
