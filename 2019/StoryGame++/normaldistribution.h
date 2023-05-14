#pragma once

#ifndef _NORMALDISTRIBUTION_H_
#define _NORMALDISTRIBUTION_H_

#include "pch.h"

const ushrt theMIN = 3;
const ushrt normaldistributionresult_InMinPercentOfMu = 5; //5%
const ushrt normaldistributionresult_InMaxPercentOfMu = 15; //15%

template <typename Ty>
inline Ty GetANormalDistributionNumber(Ty mu, float sigma)
{
	Ty MIN = (Ty)(mu * normaldistributionresult_InMinPercentOfMu / 10 + 0.5); Ty MAX = (Ty)(mu * normaldistributionresult_InMaxPercentOfMu / 10 + 0.5); // + 0.5是为了让结果四舍五入
	std::random_device seed;
	std::default_random_engine rand(seed()); std::normal_distribution<> norm(mu, sigma);
	Ty result = (Ty)(norm(rand) + 0.5); //随机正态结果四舍五入
	result = result < MIN ? MIN : result; result = result > MAX ? MAX : result;
	result = result < theMIN ? theMIN : result;
	return result;
}

#endif