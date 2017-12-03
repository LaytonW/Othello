#include <limits>

#include "utils.hpp"
#include "othello_game.hpp"

using namespace Othello;

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
                                         const OthelloPlayer player) {
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
        static_cast<OthelloRow>(
          fillTail(playerNext) ^ (opponentRow & fillTail(playerNext))
        )
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
          static_cast<OthelloRow>(
            fillTail(playerNext) ^ (opponentRow & fillTail(playerNext))
          )
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
        static_cast<OthelloRow>(
          fillTail(upperPlayerNext) ^
          (upperOpponentRow & fillTail(upperPlayerNext))
        )
      ) & upperMask : 0;

    const OthelloRow lowerMove = lowerPlayerNext & lowerOpponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(
          fillTail(lowerPlayerNext) ^
          (lowerOpponentRow & fillTail(lowerPlayerNext))
        )
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
        static_cast<OthelloRow>(
          fillTail(playerNext) ^ (opponentRow & fillTail(playerNext))
        )
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
          static_cast<OthelloRow>(
            fillTail(playerNext) ^ (opponentRow & fillTail(playerNext))
          )
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
        static_cast<OthelloRow>(
          fillTail(upperPlayerNext) ^
          (upperOpponentRow & fillTail(upperPlayerNext))
        )
      ) & upperMask : 0;

    const OthelloRow lowerMove = lowerPlayerNext & lowerOpponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(
          fillTail(lowerPlayerNext) ^
          (lowerOpponentRow & fillTail(lowerPlayerNext))
        )
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
        static_cast<OthelloRow>(
          fillTail(playerNext) ^ (opponentRow & fillTail(playerNext))
        )
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
          static_cast<OthelloRow>(
            fillTail(playerNext) ^ (opponentRow & fillTail(playerNext))
          )
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
        static_cast<OthelloRow>(
          fillTail(upperPlayerNext) ^
          (upperOpponentRow & fillTail(upperPlayerNext))
        )
      ) & upperMask : 0;

    const OthelloRow lowerMove = lowerPlayerNext & lowerOpponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(
          fillTail(lowerPlayerNext) ^
          (lowerOpponentRow & fillTail(lowerPlayerNext))
        )
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
        static_cast<OthelloRow>(
          fillTail(playerNext) ^ (opponentRow & fillTail(playerNext))
        )
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
          static_cast<OthelloRow>(
            fillTail(playerNext) ^ (opponentRow & fillTail(playerNext))
          )
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
        static_cast<OthelloRow>(
          fillTail(upperPlayerNext) ^
          (upperOpponentRow & fillTail(upperPlayerNext))
        )
      ) & upperMask : 0;

    const OthelloRow lowerMove = lowerPlayerNext & lowerOpponentRow
      ? extractFirstOne(
        static_cast<OthelloRow>(
          fillTail(lowerPlayerNext) ^
          (lowerOpponentRow & fillTail(lowerPlayerNext))
        )
      ) & lowerMask : 0;

    antiClockRotate135Moves <<= othelloRowSize;
    antiClockRotate135Moves |= (upperMove | lowerMove);
  }

  moves |= clockRotate90(clockRotate45(antiClockRotate135Moves));

  return moves;
}

const OthelloState OthelloGame::getResult(const OthelloState& state,
                                          const OthelloPlayer player,
                                          const OthelloMoves  move) {
  auto blackBitBoard = std::get<indexOf(black)>(state);
  auto whiteBitBoard = std::get<indexOf(white)>(state);
  auto& playerBoard = player == black ? blackBitBoard : whiteBitBoard;
  auto& opponentBoard = player == black ? whiteBitBoard : blackBitBoard;
  const auto tmpPlayerBoard = playerBoard;
  const auto tmpOpponentBoard = opponentBoard;
  const auto flipBoard = tmpPlayerBoard & OthelloGame::getMoves(
    player == black ? std::make_tuple(move, whiteBitBoard)
                    : std::make_tuple(blackBitBoard, move),
    player
  );

  const auto rowNum = getRowNum(move);
  const auto colNum = getColNum(move);

  const auto moveRow = getRow(move, rowNum);
  const auto flipRow = getRow(flipBoard, rowNum);
  const auto plyrRow = getRow(tmpPlayerBoard, rowNum);
  const auto oppoRow = getRow(tmpOpponentBoard, rowNum);

  const auto rowFlips = fillBetween(static_cast<OthelloRow>(moveRow | flipRow));

  opponentBoard = setRow(opponentBoard, rowNum,
                         static_cast<OthelloRow>(oppoRow & ~rowFlips));
  playerBoard = setRow(playerBoard, rowNum,
                       static_cast<OthelloRow>(plyrRow | (oppoRow & rowFlips)));

  const auto moveCol = getColumn(move, colNum);
  const auto flipCol = getColumn(flipBoard, colNum);
  const auto plyrCol = getColumn(tmpPlayerBoard, colNum);
  const auto oppoCol = getColumn(tmpOpponentBoard, colNum);

  const auto colFlips = fillBetween(static_cast<OthelloCol>(moveCol | flipCol));

  opponentBoard = setCol(opponentBoard, colNum,
                         static_cast<OthelloCol>(oppoCol & ~colFlips));
  playerBoard = setCol(playerBoard, colNum,
                       static_cast<OthelloCol>(plyrCol | (oppoCol & colFlips)));

  using _signedType = std::make_signed<decltype(rowNum)>::type;
  const auto diff =
    static_cast<_signedType>(rowNum) - static_cast<_signedType>(colNum);
  const auto diagNum = (diff + othelloRowSize) % othelloRowSize;
  const auto sum = rowNum + colNum;
  const auto antiDiagNum = sum % othelloRowSize;

  const auto moveDiag = getRow(antiClockRotate45(move), diagNum);
  const auto flipDiag = getRow(antiClockRotate45(flipBoard), diagNum);
  const auto plyrDiag = getRow(antiClockRotate45(tmpPlayerBoard), diagNum);
  const auto oppoDiag = getRow(antiClockRotate45(tmpOpponentBoard), diagNum);

  if (diagNum == 0) {
    const auto diagFlips =
      fillBetween(static_cast<OthelloRow>(moveDiag | flipDiag));
    opponentBoard = setDiag(opponentBoard, diagNum,
                            static_cast<OthelloRow>(oppoDiag & ~diagFlips));
    playerBoard = setDiag(
      playerBoard, diagNum,
      static_cast<OthelloRow>(plyrDiag | (oppoDiag & diagFlips))
    );
  } else {
    const OthelloRow lowerMask = fillTail(
      static_cast<OthelloRow>(1 << diagNum)
    );
    const OthelloRow upperMask = ~lowerMask;

    const auto upperMoveDiag = static_cast<OthelloRow>(moveDiag & upperMask);
    const auto lowerMoveDiag = static_cast<OthelloRow>(moveDiag & lowerMask);

    const auto upperFlipDiag = static_cast<OthelloRow>(flipDiag & upperMask);
    const auto lowerFlipDiag = static_cast<OthelloRow>(flipDiag & lowerMask);

    const auto diagFlips = diff > 0 ?
      fillBetween(static_cast<OthelloRow>(upperMoveDiag | upperFlipDiag))
      & upperMask :
      fillBetween(static_cast<OthelloRow>(lowerMoveDiag | lowerFlipDiag))
      & lowerMask;
    opponentBoard = setDiag(opponentBoard, diagNum,
                            static_cast<OthelloRow>(oppoDiag & ~diagFlips));
    playerBoard = setDiag(
      playerBoard, diagNum,
      static_cast<OthelloRow>(plyrDiag | (oppoDiag & diagFlips))
    );
  }

  const auto moveAntiDiag = getRow(clockRotate45(move), antiDiagNum);
  const auto flipAntiDiag = getRow(clockRotate45(flipBoard), antiDiagNum);
  const auto plyrAntiDiag = getRow(clockRotate45(tmpPlayerBoard), antiDiagNum);
  const auto oppoAntiDiag =
    getRow(clockRotate45(tmpOpponentBoard), antiDiagNum);

  if (antiDiagNum == othelloRowSize - 1) {
    const auto diagFlips =
      fillBetween(static_cast<OthelloRow>(moveAntiDiag | flipAntiDiag));
    opponentBoard = setAntiDiag(
      opponentBoard, antiDiagNum,
      static_cast<OthelloRow>(oppoAntiDiag & ~diagFlips)
    );
    playerBoard = setAntiDiag(
      playerBoard, antiDiagNum,
      static_cast<OthelloRow>(plyrAntiDiag | (oppoAntiDiag & diagFlips))
    );
  } else {
    const OthelloRow lowerMask = fillTail(
      static_cast<OthelloRow>(1 << (othelloRowSize - 2 - antiDiagNum))
    );
    const OthelloRow upperMask = ~lowerMask;

    const auto upperMoveAntiDiag =
      static_cast<OthelloRow>(moveAntiDiag & upperMask);
    const auto lowerMoveAntiDiag =
      static_cast<OthelloRow>(moveAntiDiag & lowerMask);

    const auto upperFlipAntiDiag =
      static_cast<OthelloRow>(flipAntiDiag & upperMask);
    const auto lowerFlipAntiDiag =
      static_cast<OthelloRow>(flipAntiDiag & lowerMask);

    const auto diagFlips = sum < 8 ?
      fillBetween(static_cast<OthelloRow>(upperMoveAntiDiag|upperFlipAntiDiag))
      & upperMask :
      fillBetween(static_cast<OthelloRow>(lowerMoveAntiDiag|lowerFlipAntiDiag))
      & lowerMask;
    opponentBoard = setAntiDiag(
      opponentBoard, antiDiagNum,
      static_cast<OthelloRow>(oppoAntiDiag & ~diagFlips)
    );
    playerBoard = setAntiDiag(
      playerBoard, antiDiagNum,
      static_cast<OthelloRow>(plyrAntiDiag | (oppoAntiDiag & diagFlips))
    );
  }

  playerBoard |= move;

  return std::make_tuple(blackBitBoard, whiteBitBoard);
}

void OthelloGame::applyMove(const OthelloMoves move) {
  const auto state = this->getState();
  const auto res = OthelloGame::getResult(state, this->currentPlayer, move);
  this->blackBitBoard = std::get<indexOf(black)>(res);
  this->whiteBitBoard = std::get<indexOf(white)>(res);
  this->currentPlayer = static_cast<OthelloPlayer>(-this->currentPlayer);
}

const OthelloUtility
OthelloGame::getUtility(const OthelloState& state, const OthelloPlayer player) {
  const auto blackBitBoard = std::get<indexOf(black)>(state);
  const auto whiteBitBoard = std::get<indexOf(white)>(state);
  char whiteUtility =
    countOnes(blackBitBoard) == countOnes(whiteBitBoard) ? 0 :
    countOnes(blackBitBoard) <  countOnes(whiteBitBoard) ? 1 : -1;
  return player * whiteUtility;
}

const bool OthelloGame::isTerminal(const OthelloState& state) {
  const auto blackBitBoard = std::get<indexOf(black)>(state);
  const auto whiteBitBoard = std::get<indexOf(white)>(state);
  bool filled = (blackBitBoard | whiteBitBoard) ==
    ~static_cast<OthelloBitBoard>(0);
  bool noMove = OthelloGame::getMoves(state, black) == 0 and
                OthelloGame::getMoves(state, white) == 0;
  return filled or noMove;
}

const OthelloPlayer OthelloGame::getPlayer(void) const {
  return this->currentPlayer;
}
