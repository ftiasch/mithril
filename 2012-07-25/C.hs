{-# OPTIONS_GHC -O2 #-}

import Data.List
import Data.Maybe
import Data.Char
import Data.Array.IArray
import Data.Array.Unboxed (UArray)
import Data.Int
import Data.Ratio
import Data.Bits
import Data.Function
import Data.Ord
import Control.Monad.State
import Control.Monad
import Control.Applicative
import Data.ByteString.Char8 (ByteString)
import qualified Data.ByteString.Char8 as BS
import Data.Set (Set)
import qualified Data.Set as Set
import Data.Map (Map)
import qualified Data.Map as Map
import Data.IntMap (IntMap)
import qualified Data.IntMap as IntMap
import Data.Sequence (Seq, (<|), (|>), (><), ViewL(..), ViewR(..))
import qualified Data.Sequence as Seq
import qualified Data.Foldable as F
import Data.Graph

parseInput = do
    cas <- readInt
    replicateM cas $ do
        n <- readInteger
        k <- readInteger
        return (n, k)
  where
    readInt :: State ByteString Int
    readInt = state $ fromJust . BS.readInt . BS.dropWhile isSpace
    readInteger :: State ByteString Integer
    readInteger = state $ fromJust . BS.readInteger . BS.dropWhile isSpace
    readString :: State ByteString ByteString
    readString = state $ BS.span (not . isSpace) . BS.dropWhile isSpace
    readLine :: State ByteString ByteString
    readLine = state $ BS.span (not . isEoln) . BS.dropWhile isEoln
    isEoln ch = ch == '\r' || ch == '\n'

main = do
    input <- evalState parseInput <$> BS.getContents
    let output = map solve input
    forM_ (zip [1..] output) $ \(cas, result) -> do
        print result

solve (n, k)
  | even k    = choose3 (2 * n) k
  | otherwise = choose3 (2 * n) k * 2 `mod` 3

choose3 n k
    | getFactor3 n > getFactor3 k + getFactor3 (n - k) = 0
    | otherwise                                        = ans `mod` 3
  where
    modInv3 0 = 0
    modInv3 1 = 2
    modInv3 2 = 1
    modInv3 _ = undefined

    getFactor3 n | n < 3 = 0
    getFactor3 n = (n `div` 3) + getFactor3 (n `div` 3)

    getRemain3 n | n < 3 = if n == 2 then 2 else 1
    getRemain3 n = getRemain3 (n `div` 3) * big * getRemain3 (n `mod` 3) `mod` 3
      where
        big = if even (n `div` 3) then 1 else 2

    ans = getRemain3 n * modInv3 (getRemain3 k) * modInv3 (getRemain3 (n - k))
