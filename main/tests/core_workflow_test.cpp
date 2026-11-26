#include "../universal/KPFL.h"
#include <cassert>

int main()
{
    FootballLeague league;
    league.getStadiums().push_back(Stadium(10, "National Stadium", "Kingston", 50000, "Good", 1200.0, 0));

    FootballTeam home, away;
    home.setTeamID(1); home.setTeamName("Home FC"); home.setParish("Kingston");
    away.setTeamID(2); away.setTeamName("Away FC"); away.setParish("St Andrew");
    league.registerTeam(home);
    league.registerTeam(away);

    Fixture fixture;
    fixture.setFixtureID(100);
    fixture.setFixtureDate(25, 11, 2026);
    fixture.setFixtureTime(18, 0, 0);
    fixture.setFixtureStatus("Scheduled");
    fixture.assignStadiumID(10);
    league.createFixture(fixture, league.getTeams()[0], league.getTeams()[1]);

    MatchOfficial referee(77, "Referee", 35, "M", "Referee", "A", true, 10);
    LeagueCommissioner commissioner;
    commissioner.assignOfficial(league.getFixtures()[0], referee);

    MatchResult result;
    result.setHomeScore(2);
    result.setAwayScore(1);
    league.recordFixtureResult(100, result);
    league.getFixtures()[0].completeFixture();

    assert(league.getTeams()[0].getPoints() == 3);
    assert(league.getTeams()[1].getPoints() == 0);
    assert(league.getTeams()[0].getGoalDifference() == 1);
    assert(league.getFixtures()[0].hasResult());
    assert(league.getFixtures()[0].pointsAwarded());

    Fixture restored = Fixture::fromFileString(league.getFixtures()[0].toFileString());
    assert(restored.hasResult());
    assert(restored.getStadiumID() == 10);
    assert(restored.getAssignedOfficialIDs().size() == 1);
    assert(restored.getResult().getWinner() == "Home FC");

    Stadium restoredStadium = Stadium::fromFileString(league.getStadiums()[0].toFileString());
    assert(restoredStadium.getSeatingCapacity() == 50000);
    return 0;
}
