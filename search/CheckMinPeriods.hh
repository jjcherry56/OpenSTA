// OpenSTA, Static Timing Analyzer
// Copyright (c) 2018, Parallax Software, Inc.
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef STA_MIN_PERIOD_H
#define STA_MIN_PERIOD_H

#include "DisallowCopyAssign.hh"
#include "StaState.hh"
#include "NetworkClass.hh"
#include "GraphClass.hh"
#include "SdcClass.hh"
#include "SearchClass.hh"
#include "Delay.hh"

namespace sta {

class MinPeriodCheckVisitor;

class CheckMinPeriods
{
public:
  explicit CheckMinPeriods(StaState *sta);
  ~CheckMinPeriods();
  void clear();
  // All violating min period checks.
  // corner=NULL checks all corners.
  MinPeriodCheckSeq &violations(const Corner *corner);
  // Min period check with the least slack.
  // corner=NULL checks all corners.
  MinPeriodCheck *minSlackCheck(const Corner *corner);

protected:
  void visitMinPeriodChecks(MinPeriodCheckVisitor *visitor);
  void visitMinPeriodChecks(Vertex *vertex,
			    MinPeriodCheckVisitor *visitor);

  MinPeriodCheckSeq checks_;
  StaState *sta_;

private:
  DISALLOW_COPY_AND_ASSIGN(CheckMinPeriods);
};

class MinPeriodCheck
{
public:
  MinPeriodCheck(Pin *pin, Clock *clk);
  MinPeriodCheck *copy();
  Pin *pin() const { return pin_; }
  Clock *clk() const { return clk_; }
  float period() const;
  float minPeriod(const StaState *sta) const;
  Slack slack(const StaState *sta) const;

private:
  DISALLOW_COPY_AND_ASSIGN(MinPeriodCheck);

  Pin *pin_;
  Clock *clk_;
};

class MinPeriodSlackLess
{
public:
  explicit MinPeriodSlackLess(StaState *sta);
  bool operator()(const MinPeriodCheck *check1,
		  const MinPeriodCheck *check2) const;

private:
 const StaState *sta_;
};

} // namespace
#endif