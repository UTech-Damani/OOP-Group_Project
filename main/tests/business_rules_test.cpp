#include "../universal/KPFL.h"
#include <cassert>

int main()
{
    FootballLeague league;
    league.addStadiums(Stadium(1, "Stadium", "Kingston", 2, "Good", 50.0, 0));

    FootballTeam a, b;
    a.setTeamID(1); a.setTeamName("A");
    b.setTeamID(2); b.setTeamName("B");
    league.registerTeam(a);
    league.registerTeam(b);

    Fixture fixture;
    fixture.setFixtureID(1);
    fixture.setFixtureDate(1, 1, 2027);
    fixture.setFixtureTime(10, 0, 0);
    fixture.setFixtureStatus("Scheduled");
    fixture.assignStadiumID(1);
    league.createFixture(fixture, league.getTeams()[0], league.getTeams()[1]);

    bool rejected = false;
    try { league.getFixtures()[0].completeFixture(); }
    catch (const FixtureIncompleteException&) { rejected = true; }
    assert(rejected);

    rejected = false;
    try {
        Fixture conflict = fixture;
        conflict.setFixtureID(2);
        league.createFixture(conflict, league.getTeams()[0], league.getTeams()[1]);
    }
    catch (const SchedulingConflictException&) { rejected = true; }
    assert(rejected);

    rejected = false;
    try { MatchResult bad; bad.setHomeScore(-1); }
    catch (const InvalidScoreException&) { rejected = true; }
    assert(rejected);

    Stadium tiny(9, "Tiny", "Kingston", 1, "Good", 10.0, 0);
    tiny.sellTickets(1);
    rejected = false;
    try { tiny.sellTickets(1); }
    catch (const CapacityExceededException&) { rejected = true; }
    assert(rejected);

    Spectator spectator(4, "Spectator", 20, "F", 0, 0.0, 0.0);
    Merchandise product("M", "Brand", 5, "Cap", 115.0, 1);
    StadiumShop shop;
    shop.addProduct(&product, false);
    rejected = false;
    try { shop.transactionWithCash(&spectator, &product, 100.0); }
    catch (const InsufficientPaymentException&) { rejected = true; }
    assert(rejected);

    double change = shop.transactionWithCash(&spectator, &product, 120.0);
    assert(change == 5.0);
    assert(product.getQuantityInStock() == 0);
    return 0;
}
